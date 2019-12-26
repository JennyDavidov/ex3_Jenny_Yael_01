//
// Created by yael6 on 23/12/2019.
//
#include "xml.h"
#include <array>

using namespace std;
string xmlDetails[36];

void readingXml() {
    xmlDetails[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";//1
    xmlDetails[1] = "/sim/time/warp";//2
    xmlDetails[2] = "/controls/switches/magnetos";//3
    xmlDetails[3] = "/instrumentation/heading-indicator/offset-deg";//4
    xmlDetails[4] = "/instrumentation/altimeter/indicated-altitude-ft";//5
    xmlDetails[5] = "/instrumentation/altimeter/pressure-alt-ft";//6
    xmlDetails[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";//7
    xmlDetails[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";//8
    xmlDetails[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";//9
    xmlDetails[9] = "/instrumentation/attitude-indicator/internal-roll-deg";//10
    xmlDetails[10] = "/instrumentation/encoder/indicated-altitude-ft";//11
    xmlDetails[11] = "/instrumentation/encoder/pressure-alt-ft";//12
    xmlDetails[12] = "/instrumentation/gps/indicated-altitude-ft";//13
    xmlDetails[13] = "/instrumentation/gps/indicated-ground-speed-kt";//14
    xmlDetails[14] = "/instrumentation/gps/indicated-vertical-speed";//15
    xmlDetails[15] = "/instrumentation/heading-indicator/indicated-heading-deg";//16
    xmlDetails[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";//17
    xmlDetails[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";//18
    xmlDetails[18] = "/instrumentation/turn-indicator/indicated-turn-rate";//19
    xmlDetails[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";//20
    xmlDetails[20] = "/controls/flight/aileron";//21
    xmlDetails[21] = "/controls/flight/elevator";//22
    xmlDetails[22] = "/controls/flight/rudder";//23
    xmlDetails[23] = "/controls/flight/flaps";//24
    xmlDetails[24] = "/controls/engines/engine/throttle";//25
    xmlDetails[25] = "/controls/engines/current-engine/throttle";//26
    xmlDetails[26] = "/controls/switches/master-avionics";//27
    xmlDetails[27] = "/controls/switches/starter";//28
    xmlDetails[28] = "/engines/active-engine/auto-start";//29
    xmlDetails[29] = "/controls/flight/speedbrake";//30
    xmlDetails[30] = "/sim/model/c172p/brake-parking";//31
    xmlDetails[31] = "/controls/engines/engine/primer";//32
    xmlDetails[32] = "/controls/engines/current-engine/mixture";//33
    xmlDetails[33] = "/controls/switches/master-bat";//34
    xmlDetails[34] = "/controls/switches/master-alt";//35
    xmlDetails[35] = "/engines/engine/rpm";//36
}
