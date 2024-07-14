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
    string rec_path = "/home/theia-onboard-media/input/recordings/curtains_clip__v3.0.1.raw";
    string output_path = "/home/theia-onboard-media/output/recordings/recfile_open_test__recent.raw";

    int start_delay = 1;

    Metavision::Camera theia_cam;
    // Attempting to open the camera when you plug in the usb
    try {
        theia_cam = Metavision::Camera::from_file(rec_path);

    } catch (Metavision::CameraException &e) { // catching the exception if we can't find cam
        cout << e.what() << endl;
    }

    // to analyze the events, we add a callback that will be called periodically to give access to the latest events
    theia_cam.cd().add_callback(get_events);
    
    this_thread::sleep_for(chrono::seconds(start_delay));

    // start the camera recording to a specified filepath and streams data
    theia_cam.start();
    
    cout << "Recording opened." << endl;

    theia_cam.start_recording(output_path);

    auto start_t = chrono::system_clock::now();

    while (theia_cam.is_running()) {
        ;
    }


    if (theia_cam.is_running() != true) {
        cout << "Stopped recording. File saved to " << output_path << endl;
    }
      
   
    
    // shut down the camera
    theia_cam.stop();
}