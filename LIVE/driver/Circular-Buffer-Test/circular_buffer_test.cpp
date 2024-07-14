#include <metavision/sdk/driver/camera.h>
#include <metavision/sdk/base/events/event_cd.h>
#include <opencv4/opencv2/core.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <iomanip> // for std::put_money
#include <atomic>
#include <unistd.h>

using namespace std;

class CircularBuffer {
public:
    CircularBuffer(size_t size) : buffer(size), head(0), tail(0), full(false) {
        cout << "CircularBuffer initialized with size: " << format_number(size) << " events (" 
             << format_number(size * sizeof(Metavision::EventCD)) << " bytes)" << endl;
    }

    void push(const Metavision::EventCD* begin, const Metavision::EventCD* end) {
        std::unique_lock<std::mutex> lock(mutex);
        size_t event_count = 0;
        for (const Metavision::EventCD* ev = begin; ev != end; ++ev) {
            buffer[head] = *ev; // Write event to buffer at position `head`
            head = (head + 1) % buffer.size(); // Increment and wrap `head`
            if (full) {
                tail = (tail + 1) % buffer.size(); // Increment and wrap `tail` if buffer is full
            }
            full = head == tail; // Set full flag if `head` catches up to `tail`
            event_count++;
        }
        cv.notify_one(); // Notify any waiting thread
        cout << "Pushed " << format_number(event_count) << " events to buffer, head=" << format_number(head) 
             << ", tail=" << format_number(tail) << ", full=" << full << endl;
    }

    bool pop(vector<Metavision::EventCD>& events) {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this] { return full || head != tail; }); // Wait for data to be available

        cout << "Popping events from buffer, head=" << format_number(head) << ", tail=" << format_number(tail) << ", full=" << full << endl;
        size_t event_count = 0;
        while (tail != head || full) {
            if (tail >= buffer.size()) {
                cerr << "Error: tail index out of bounds: " << format_number(tail) << endl;
                return false;
            }
            events.push_back(buffer[tail]); // Read event from buffer at position `tail`
            tail = (tail + 1) % buffer.size(); // Increment and wrap `tail`
            if (full) {
                full = false; // Clear full flag when a single event is read
            }
            event_count++;
        }

        cout << "Popped " << format_number(event_count) << " events from buffer, new tail=" << format_number(tail) << endl;
        return !events.empty();
    }

    size_t get_event_count() const {
        std::unique_lock<std::mutex> lock(mutex);
        if (full) {
            return buffer.size();
        } else if (head >= tail) {
            return head - tail;
        } else {
            return buffer.size() - tail + head;
        }
    }

    bool is_full() {
        std::unique_lock<std::mutex> lock(mutex);
        return full;
    }

    void set_full() {
        std::unique_lock<std::mutex> lock(mutex);
        full = true;
        cv.notify_one();
        cout << "Buffer set to full." << endl;
    }

    static std::string format_number(size_t number) {
        std::ostringstream ss;
        ss.imbue(std::locale(""));
        ss << std::fixed << number;
        return ss.str();
    }

private:
    vector<Metavision::EventCD> buffer; // Buffer to hold events
    size_t head; // Index for writing
    size_t tail; // Index for reading
    bool full; // Buffer full flag
    size_t buffer_size; // Total size of the buffer
    mutable std::mutex mutex; // Mutex for synchronization
    std::condition_variable cv; // Condition variable for synchronization
};

CircularBuffer event_buffer(250000); // Adjust the size to handle up to 1M events per second
std::atomic<bool> recording_stopped(false); // Flag to indicate recording status

void get_events(const Metavision::EventCD* begin, const Metavision::EventCD* end) {
    if (event_buffer.is_full()) {
        cerr << "Buffer is full. Exiting to prevent data loss." << endl;
        exit(EXIT_FAILURE);
    }
    if (begin != nullptr && end != nullptr && begin != end) {
        event_buffer.push(begin, end);
    } else {
        cerr << "Invalid event range received." << endl;
    }
}

void process_and_save_events(string output_path) {
    cout << "Process and save thread started." << endl;
    ofstream output_file(output_path, ios::binary | ios::out);
    if (!output_file.is_open()) {
        cerr << "Failed to open output file: " << output_path << endl;
        return;
    }

    while (!recording_stopped || event_buffer.get_event_count() > 0) {
        vector<Metavision::EventCD> events;
        if (!event_buffer.pop(events)) {
            if (!event_buffer.is_full()) {
                cout << "No events to process, exiting thread." << endl;
                break;
            }
        }

        cout << "Processing " << CircularBuffer::format_number(events.size()) << " events." << endl;
        for (const auto& ev : events) {
            // Process event (this example just writes them to a file)
            output_file.write(reinterpret_cast<const char*>(&ev), sizeof(ev));
        }

        cout << "Events in buffer after processing: " << CircularBuffer::format_number(event_buffer.get_event_count()) << endl;
        events.clear();
    }

    output_file.close();
    cout << "Events processed and saved." << endl;
}

void print_memory_usage() {
    pid_t pid = getpid();
    stringstream ss;
    ss << "/proc/" << pid << "/status";
    ifstream status_file(ss.str());
    string line;
    while (getline(status_file, line)) {
        if (line.find("VmRSS:") != string::npos) {
            cout << line << endl;
        }
    }
}

void print_system_info() {
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) == 0) {
        cout << "Available threads: " << thread::hardware_concurrency() << endl;
        cout << "Used threads: " << 2 << endl; // since we use 2 threads in this example
        cout << "Memory allocated: " << CircularBuffer::format_number(sys_info.totalram - sys_info.freeram) << " bytes" << endl;
    }
}

int main(void) {
    string output_path = "/home/theia-onboard-media/output/recordings/circular_buffer_test__recent.raw";

    int start_delay = 1;
    int recording_length = 1;

    Metavision::Camera theia_cam;
    try {
        theia_cam = Metavision::Camera::from_first_available();
        cout << "Camera opened successfully." << endl;
    } catch (Metavision::CameraException& e) {
        cout << "Failed to open camera: " << e.what() << endl;
        return 1;
    }

    theia_cam.cd().add_callback(get_events);
    cout << "Callback added." << endl;

    std::thread processing_thread(process_and_save_events, output_path);

    this_thread::sleep_for(chrono::seconds(start_delay));
    theia_cam.start();
    cout << "Recording started." << endl;
    theia_cam.start_recording(output_path);

    auto start_t = chrono::system_clock::now();

    print_memory_usage(); // Print memory usage at the start

    while (theia_cam.is_running()) {
        auto current_t = chrono::system_clock::now();
        auto elapsed_time = chrono::duration_cast<chrono::seconds>(current_t - start_t).count();

        if (elapsed_time >= recording_length) {
            theia_cam.stop_recording();
            theia_cam.stop();
            break;
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout << "Recording stopped, notifying processing thread." << endl;
    recording_stopped = true;
    event_buffer.set_full();
    processing_thread.join();
    cout << "Processing thread joined." << endl;

    if (!theia_cam.is_running()) {
        cout << "Stopped recording. File saved to " << output_path << endl;
    }

    print_memory_usage(); // Print memory usage at the end
    print_system_info();

    return 0;
}
