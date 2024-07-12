#ifndef SCRIPTSTATISTICS_HPP
#define SCRIPTSTATISTICS_HPP



#include <iostream>
#include <chrono>

using namespace std;
using chrono_object = chrono::_V2::system_clock::time_point;


class ScriptStatistics {
public:

    string recording_name = "empty";

    int input_counter = 0;
    int output_counter = 0;
    float rec_duration = 0.0;
    float input_ev_rate = 0.0;
    float processing_ev_rate = 0.0;

    float processing_runtime = 0.0;
    float global_runtime = 0.0;


    void initScrptStat(string rec_name) {

        recording_name = rec_name;

    };

    string thousands_format(int n) {

        string result = to_string(n);

        for (int i = result.size() - 3; i > 0; i -= 3) {
            result.insert(i, ",");
        }

        return result;
    }

    string human_readable_time(Metavision::timestamp t) {
        ostringstream oss;
        array<string, 6> ls{"d", "h", "m", "s", "ms", "us"};
        array<int, 6> vs;
        vs[5] = (t % 1000);
        t /= 1000; // ms
        vs[4] = (t % 1000);
        t /= 1000; // s
        vs[3] = (t % 60);
        t /= 60; // m
        vs[2] = (t % 60);
        t /= 60; // h
        vs[1] = (t % 24);
        t /= 24; // d
        vs[0] = (t % 365);

        size_t i = 0;
        for (; i < 6 && vs[i] == 0; ++i) {}
        for (; i < 6; ++i) {
            oss << vs[i] << ls[i] << " ";
        }
        return oss.str();
    };

    void calculateScrptStat(chrono_object globalstart, chrono_object processingstart, chrono_object globalend, float duration) {

        rec_duration = duration / 1.e3;

        chrono::duration<float> processingruntime = globalend - processingstart;
        processing_runtime = processingruntime.count();
        chrono::duration<float> globalruntime = globalend - globalstart;
        global_runtime = globalruntime.count();

        input_ev_rate = (input_counter / (rec_duration / 1.e3));
        processing_ev_rate = (input_counter / processing_runtime);

        cout << "Recording identity: " << recording_name << endl;
        cout << "\nDuration is " << human_readable_time(duration) << " with " << thousands_format(input_counter) << " events." << endl;
        cout << "   → source datarate: " << thousands_format(input_ev_rate) << " Ev/s\n" << endl;
        cout << "Total asynchronous_timesurface_test runtime: " << global_runtime << "s\n" << endl;
        cout << "Processing section runtime: " << processing_runtime << "s → " << thousands_format(output_counter) << " events after filtering." << endl;
        cout << "   → approximate processing speed: " << thousands_format(processing_ev_rate) << " Ev/s\n" << endl;

    };

};



#endif