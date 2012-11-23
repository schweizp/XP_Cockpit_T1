#ifndef FLIPSWITCH_H
#define FLIPSWITCH_H

// for syntax highlighting purposes
#include "usb_api.h"
#include <Bounce.h>

// hardware objects
Bounce        tModeOff(28, 10);                    // Transponder rotary switch Mode selector...
Bounce        tModeSby(29, 10);
Bounce        tModeOn(30, 10);
Bounce        tModeAlt(31, 10);
Bounce        tModeTest(32, 10);

// X-Plane objects
FlightSimCommand TransponderOFF;
FlightSimCommand TransponderSTDBY;
FlightSimCommand TransponderON;
FlightSimCommand TransponderALT;
FlightSimCommand TransponderTEST;

// setup function is called once when Teensy boots up
void setup_flipswitch()
{
    // initialize hardware pins
    pinMode(28, INPUT_PULLUP);
    pinMode(29, INPUT_PULLUP);
    pinMode(30, INPUT_PULLUP);
    pinMode(31, INPUT_PULLUP);
    pinMode(32, INPUT_PULLUP);

    // configure the X-Plane variables
    TransponderOFF = XPlaneRef("sim/transponder/transponder_off");
    TransponderSTDBY = XPlaneRef("sim/transponder/transponder_standby");
    TransponderON = XPlaneRef("sim/transponder/transponder_on");
    TransponderALT = XPlaneRef("sim/transponder/transponder_alt");
    TransponderTEST = XPlaneRef("sim/transponder/transponder_test");
}

// loop function is called repeteadtly as long as Teensy is powered
void loop_flipswitch()
{
    // read state of input pins and set corresponding
    // state in X-Pane variable
    if (tModeOff.update())
        if (tModeOff.read() == LOW)
            TransponderOFF.once();
    if (tModeSby.update())
        if (tModeSby.read() == LOW)
            TransponderSTDBY.once();
    if (tModeOn.update())
        if (tModeOn.read() == LOW)
            TransponderON.once();
    if (tModeAlt.update())
        if (tModeAlt.read() == LOW)
            TransponderALT.once();
    if (tModeTest.update())
        if (tModeTest.read() == LOW)
            TransponderTEST.once();
}


#endif // FLIPSWITCH_H
