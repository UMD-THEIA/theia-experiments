#include <metavision/sdk/driver/camera.h>
#include <metavision/sdk/driver/biases.h>
#include <metavision/sdk/base/events/event_cd.h>
#include <opencv4/opencv2/core.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

using namespace std;

void get_events(const Metavision::EventCD *begin, const Metavision::EventCD *end) {
    int counter = 0;

// this loop allows us to get access to each event received in this callback
    for (const Metavision::EventCD *ev = begin; ev != end; ++ev) {
        ++counter; // count each event

        // print each event
        // cout << "Event received: coordinates (" << ev->x << ", " << ev->y << "), t: " << ev->t
        //           << ", polarity: " << ev->p << std::endl;
    }
    cout << "There were " << counter << " events in this callback." << endl;

}

int main(void) {

    // IMPLEMENT A WAY TO NOT WRITE OVER EXISTING FILE
    string bias_path = "/home/theia-onboard-media/input/biases/recording_2024-02-03_22-17-27.bias";
    string output_path = "/home/theia-onboard-media/output/recordings/recording_test__recent.raw";

    int start_delay = 1;
    int recording_length = 1;

    Metavision::Camera theia_cam;
    // Attempting to open the camera when you plug in the usb
    try {
        theia_cam = Metavision::Camera::from_first_available();

    } catch (Metavision::CameraException &e) { // catching the exception if we can't find cam
        cout << e.what() << endl;
    }

    // to analyze the events, we add a callback that will be called periodically to give access to the latest events
    theia_cam.cd().add_callback(get_events);
    
    this_thread::sleep_for(chrono::seconds(start_delay));

    // start the camera recording to a specified filepath and streams data
    theia_cam.start();
    theia_cam.biases().set_from_file(bias_path);
    
    cout << "Recording opened." << endl;

    theia_cam.start_recording(output_path);

    auto start_t = chrono::system_clock::now();

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


    if (theia_cam.is_running() != true) {
        cout << "Stopped recording. File saved to " << output_path << endl;
    }
      
}