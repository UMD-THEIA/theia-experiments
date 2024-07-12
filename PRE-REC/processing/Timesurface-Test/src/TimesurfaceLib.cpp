#include <metavision/sdk/driver/camera.h>
#include <metavision/sdk/base/events/event_cd.h>
#include <iostream>

#include "../include/StarfieldProcessorVariables.hpp"
#include "../include/ScriptStatistics.hpp"

using namespace std;



// functions for processing events
void timesurface(const Metavision::EventCD *begin, const Metavision::EventCD *end, StarfieldProcessorVariables &SPVar, ScriptStatistics &ScrptStat) {
    for (const Metavision::EventCD *ev = begin; ev != end; ++ev) {

        ScrptStat.input_counter += 1;

        float eventTime = (ev->t) / 1.e6;
        SPVar.t[ev->x][ev->y] = eventTime;
        SPVar.set_ROI(ev->x, ev->y);
        SPVar.update_ROI(eventTime);
        if (SPVar.surface_activation_test())
            ScrptStat.output_counter += 1;

        SPVar.reset_dynamic_variables();

    };
};