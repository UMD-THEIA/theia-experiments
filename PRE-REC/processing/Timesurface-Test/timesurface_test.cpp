#include <metavision/sdk/driver/camera.h>
#include <metavision/sdk/driver/biases.h>
#include <metavision/sdk/base/events/event_cd.h>
#include <opencv4/opencv2/core.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <syncstream>
#include <ctime>
#include <fstream>
#include <filesystem>

#include "filepath_config.hpp"
#include "include/StarfieldProcessorVariables.hpp"
#include "include/TimesurfaceLib.hpp"
#include "include/ScriptStatistics.hpp"

using namespace std;



// callback to save events to raw file
void save_events(const Metavision::EventCD *begin, const Metavision::EventCD *end) {
    ;
};


// class to handle events in processing callback
class StarfieldProcessor {
public:

    // variable storage objects
    StarfieldProcessorVariables SPVar;
    ScriptStatistics ScrptStat;


    void initSP() {

        SPVar.initSPV();
        ScrptStat.initScrptStat(rec_name);

    };

    void process_events(const Metavision::EventCD *begin, const Metavision::EventCD *end) {
        
        // thread processing_thread(timesurface, begin, end, SPVar);
        // processing_thread.join();
        timesurface(begin, end, SPVar, ScrptStat);

    };
};




int main(void) {

    cout << "Entering script\n" << endl;

    // get full script start time and initialize statistics object
    auto globalstart = chrono::high_resolution_clock::now();

    cout << "Attempting to open Metavision::Camera. . .\n" << endl;

    // open the Metavision::Camera object
    Metavision::Camera theia_cam;
    try {
        theia_cam = Metavision::Camera::from_file(rec_path);
    } catch (Metavision::CameraException &e) {
        cout << e.what() << endl;
    }
    Metavision::timestamp duration = -1;
    try {
        auto &osc = theia_cam.offline_streaming_control();
        while (!osc.is_ready()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        duration = osc.get_duration();
    } catch (const Metavision::CameraException &) {}

    cout << "Success. Initializing callbacks. . .\n" << endl;

    // initialize callback to save events to raw file
    theia_cam.cd().add_callback(save_events);

    // initialize callback to process events
    StarfieldProcessor StarProc;
    StarProc.initSP();
    theia_cam.cd().add_callback([&StarProc](const Metavision::EventCD *ev_begin, const Metavision::EventCD *ev_end) {
        StarProc.process_events(ev_begin, ev_end);
    });



    cout << "Success. Waiting to begin. . ." << endl;

    // sleep thread until intended start time
    this_thread::sleep_for(chrono::seconds(start_delay));

    cout << "Beginning processing.\n" << endl;
    
    // camera driver script
        // (for explanations, see Pipeline-Development/cpp/driver/recording file open test/)
    theia_cam.start();
    cout << "\nRecording opened." << endl;
    theia_cam.start_recording(output_path);

    // get processing start time
    auto processingstart = chrono::high_resolution_clock::now();
    cout << "Processing. . ." << endl;

    auto start_t = chrono::system_clock::now();
    while (theia_cam.is_running()) {
        ;
    }
    if (theia_cam.is_running() != true) {
        cout << "Recording closed. Copy saved to " << output_path << endl;
    }
    theia_cam.stop();


    // get full script end time
    auto globalend = chrono::high_resolution_clock::now();

    // calculate and print statistics
    StarProc.ScrptStat.calculateScrptStat(globalstart, processingstart, globalend, duration);

    return 0;

}