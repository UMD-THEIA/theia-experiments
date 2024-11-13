#include <metavision/hal/utils/hal_exception.h>
#include <metavision/hal/facilities/i_ll_biases.h>
#include <metavision/hal/facilities/i_monitoring.h>
#include <metavision/hal/facilities/i_device_control.h>
#include <metavision/hal/facilities/i_decoder.h>
#include <metavision/hal/facilities/i_event_decoder.h>
#include <metavision/hal/facilities/i_plugin_software_info.h>
#include <metavision/hal/facilities/i_hw_identification.h>
#include <metavision/hal/device/device.h>
#include <metavision/hal/device/device_discovery.h>
#include <metavision/hal/facilities/i_events_stream.h>
#include <metavision/sdk/base/events/event_cd.h>

#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <iomanip> // for std::put_money
#include <unistd.h>
#include <sstream>
#include <fstream>

using namespace std;
namespace po = boost::program_options;

std::string format_number(size_t number) {
    std::ostringstream ss;
    ss.imbue(std::locale(""));
    ss << std::fixed << number;
    return ss.str();
}

void print_system_info() {
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) == 0) {
        cout << "Available threads: " << thread::hardware_concurrency() << endl;
        cout << "Used threads: " << 2 << endl; // since we use 2 threads in this example
    }
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

int main(int argc, char* argv[]) {

    string plugin_name;
    long system_id = -1;

    // camera serial
    string serial = "";

    string output_path;
    int start_delay = 1;
    int recording_duration = 1;

    // Define options
    po::options_description desc("Usage");
    desc.add_options()
        ("help,h", "Show help message")
        ("output,o", po::value<string>(&output_path)->required(), "Set output filename in /home/theia-onboard-media/output/recordings (required)")
        ("delay,s", po::value<int>(&start_delay)->default_value(1), "Set start delay in seconds (default: 1)")
        ("duration,d", po::value<int>(&recording_duration)->default_value(1), "Set recording length in seconds (default: 1)");

    // Parse options
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }

        po::notify(vm); // Check for required options
    } catch (const po::error& e) {
        cerr << "Error: " << e.what() << "\n";
        cerr << desc << "\n";
        return 1;
    }

    // Output parsed values
    cout << "Recording name: " << output_path << "\n";
    output_path = "/home/theia-media/output/recordings/" + output_path;
    cout << "Output path: " << output_path << "\n";
    cout << "Delay: " << start_delay << "s\n";
    cout << "Recording duration: " << recording_duration << "s\n";

    // // IMPLEMENT A WAY TO NOT WRITE OVER EXISTING FILE
    // string output_path = "/home/theia-onboard-media/output/recordings/eventsstream_test__recent.raw";

    // int start_delay = 1;
    // int recording_duration = 5;

    // Open the device
    std::cout << "Opening camera..." << std::endl;
    std::unique_ptr<Metavision::Device> device;
    try {
        device = Metavision::DeviceDiscovery::open(serial);
    } catch (Metavision::HalException &e) { std::cout << "Error exception: " << e.what() << std::endl; }

    if (!device) {
        std::cerr << "Camera opening failed." << std::endl;
        return 1;
    }
    std::cout << "Camera open." << std::endl;

    Metavision::I_PluginSoftwareInfo *i_pluginsoftwareinfo = device->get_facility<Metavision::I_PluginSoftwareInfo>();
    if (i_pluginsoftwareinfo) {
        plugin_name = i_pluginsoftwareinfo->get_plugin_name();
        std::cout << "Plugin used: " << plugin_name << std::endl;
    }

    Metavision::I_HW_Identification *i_hw_identification = device->get_facility<Metavision::I_HW_Identification>();
    if (i_hw_identification) {
        system_id = i_hw_identification->get_system_id();
        std::cout << "System ID: " << system_id << std::endl;
    }

    Metavision::I_DeviceControl *i_device_control = device->get_facility<Metavision::I_DeviceControl>();
    if (!i_device_control) {
        std::cerr << "Could not get Device Control facility." << std::endl;
        return 1;
    }

    // print_memory_usage(); // Print memory usage at the start

    this_thread::sleep_for(chrono::seconds(start_delay));

    Metavision::I_EventsStream *i_eventsstream = device->get_facility<Metavision::I_EventsStream>();
    if (i_eventsstream) {
        if (output_path != "") {
            
            i_eventsstream->log_raw_data(output_path);

            i_eventsstream->start();
            i_device_control->start();
            std::cout << "Camera started." << std::endl;

            auto start_t = chrono::system_clock::now();

            while (chrono::duration_cast<chrono::seconds>(chrono::system_clock::now() - start_t).count() < recording_duration) {
                long n_bytes;
                uint8_t *raw_data = i_eventsstream->get_latest_raw_data(n_bytes);
                ;
            }

            i_eventsstream->stop_log_raw_data();
        }
    } else {
        std::cerr << "Could not initialize events stream." << std::endl;
        return 3;
    }

    cout << "Stopped recording. File saved to " << output_path << endl;

    // print_memory_usage(); // Print memory usage at the end
    print_system_info();

    return 0;
}
