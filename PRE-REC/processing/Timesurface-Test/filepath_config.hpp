#ifndef FILEPATH_CONFIG_HPP
#define FILEPATH_CONFIG_HPP



using namespace std;

// duration to wait until starting Metavision::Camera object
int start_delay = 1;
// source recording.raw path
string rec_path = "/home/theia-onboard-media/input/recordings/blackwater1_rec1_slew7_OpenEB-3.0.1.raw";
// source recording.raw nickname
string rec_name = "Blackwater Refuge Rec. 1, Slew 7";
// saved recording.raw path (will just duplicate original recording)
string output_path = "/home/theia-onboard-media/output/recordings/asynchronous_timesurface_test__recent.raw";



#endif