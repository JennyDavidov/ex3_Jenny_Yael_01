//
// Created by yael6 on 23/12/2019.
//
#include "xml.h"
using namespace std;

vector<string> readingXml(){
    vector<string> xmlDetails;
    xmlDetails.push_back("/instrumentation/airspeed-indicator/indicated-speed-kt");//1
    xmlDetails.push_back("/sim/time/warp");//2
    xmlDetails.push_back("/controls/switches/magnetos");//3
    xmlDetails.push_back("/instrumentation/heading-indicator/offset-deg");//4
    xmlDetails.push_back("/instrumentation/altimeter/indicated-altitude-ft");//5
    xmlDetails.push_back("/instrumentation/altimeter/pressure-alt-ft");//6
    xmlDetails.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");//7
    xmlDetails.push_back("/instrumentation/attitude-indicator/indicated-roll-deg");//8
    xmlDetails.push_back("/instrumentation/attitude-indicator/internal-pitch-deg");//9
    xmlDetails.push_back("/instrumentation/attitude-indicator/internal-roll-deg");//10
    xmlDetails.push_back("/instrumentation/encoder/indicated-altitude-ft");//11
    xmlDetails.push_back("/instrumentation/encoder/pressure-alt-ft");//12
    xmlDetails.push_back("/instrumentation/gps/indicated-altitude-ft");//13
    xmlDetails.push_back("/instrumentation/gps/indicated-ground-speed-kt");//14
    xmlDetails.push_back("/instrumentation/gps/indicated-vertical-speed");//15
    xmlDetails.push_back("/instrumentation/heading-indicator/indicated-heading-deg");//16
    xmlDetails.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");//17
    xmlDetails.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");//18
    xmlDetails.push_back("/instrumentation/turn-indicator/indicated-turn-rate");//19
    xmlDetails.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");//20
    xmlDetails.push_back("/controls/flight/aileron");//21
    xmlDetails.push_back("/controls/flight/elevator");//22
    xmlDetails.push_back("/controls/flight/rudder");//23
    xmlDetails.push_back("/controls/flight/flaps");//24
    xmlDetails.push_back("/controls/engines/engine/throttle");//25
    xmlDetails.push_back("/controls/engines/current-engine/throttle");//26
    xmlDetails.push_back("/controls/switches/master-avionics");//27
    xmlDetails.push_back("/controls/switches/starter");//28
    xmlDetails.push_back("/engines/active-engine/auto-start");//29
    xmlDetails.push_back("/controls/flight/speedbrake");//30
    xmlDetails.push_back("/sim/model/c172p/brake-parking");//31
    xmlDetails.push_back("/controls/engines/engine/primer");//32
    xmlDetails.push_back("/controls/engines/current-engine/mixture");//33
    xmlDetails.push_back("/controls/switches/master-bat");//34
    xmlDetails.push_back("/controls/switches/master-alt");//35
    xmlDetails.push_back("/engines/engine/rpm");//36

    return xmlDetails;
}
