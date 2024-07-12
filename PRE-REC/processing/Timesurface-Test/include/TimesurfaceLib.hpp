#ifndef TIMESURFACELIB_HPP
#define TIMESURFACELIB_HPP



#include <metavision/sdk/driver/camera.h>
#include <metavision/sdk/base/events/event_cd.h>
#include <iostream>

#include "../include/StarfieldProcessorVariables.hpp"
#include "../include/ScriptStatistics.hpp"


void timesurface(const Metavision::EventCD *begin, const Metavision::EventCD *end, StarfieldProcessorVariables &SPVar, ScriptStatistics &ScrptStat);



#endif