#ifndef FILEPATH_CONFIG_HPP
#define FILEPATH_CONFIG_HPP



using namespace std;

// duration to wait until starting Metavision::Camera object
int start_delay = 1;
// source recording.raw path
string rec_path = "/home/theia-onboard-media/input/recordings/frame_clip__v3.0.1.raw";
// source recording.raw nickname
string rec_name = "Non-star picture frame testing clip";
// saved recording.raw path (will just duplicate original recording)
string output_path = "/home/theia-onboard-media/output/recordings/asynchronous_timesurface_test__recent.raw";



#endif