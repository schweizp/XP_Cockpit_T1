#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

// for syntax highlighting purposes
#include "usb_api.h"
#include <Bounce.h>

Bounce      shift_1(8, 10);         // COM1 shift big to small increment
Bounce      act_stdby_1(9, 10);     // COM1 Active / Stdby button
Bounce      shift_2(36, 10);        // NAV1 shift big to small increment
Bounce      act_stdby_2(10, 10);    // NAV1 Active / Stdby button
Bounce      shift_3(26, 10);        // COM2 shift big to small increment
Bounce      act_stdby_3(11, 10);    // COM2 Active / Stdby button
Bounce      shift_4(37,10);         // NAV2 shift big to small increment
Bounce      act_stdby_4(41, 10);    // NAV2 Active / Stdby button
Bounce      adf_1(13, 10);          // ADF Buttons....
Bounce      adf_10(14, 10);
Bounce      adf_100(15, 10);
Bounce      act_stdby_5(16, 10);
Bounce      trans_1(33, 10);        // Transponder buttons
Bounce      trans_10(34, 10);
Bounce      trans_100(35, 10);
Bounce      trans_1000(43, 10);
Bounce      OBSsel_6(40, 10);       // Select OBS1 or OBS2
Bounce      dmeNAV1(44, 10);        // DME mode select buttons
Bounce      dmeNAV2(45, 10);

// X-Plane objects
FlightSimCommand COM1StdbyFlip;
FlightSimCommand COM2StdbyFlip;
FlightSimCommand NAV1StdbyFlip;
FlightSimCommand NAV2StdbyFlip;
FlightSimCommand ADFStdbyFlip;
FlightSimCommand ADFHundredsUp;
FlightSimCommand ADFTensUp;
FlightSimCommand ADFOnesUp;
FlightSimCommand TransponderThousandsUp;
FlightSimCommand TransponderHundredsUp;
FlightSimCommand TransponderTensUp;
FlightSimCommand TransponderOnesUp;
FlightSimInteger DMESelectSource;

// variables
boolean com1_big = true;    // is big or small increment selected
boolean com2_big = true;    // is big or small increment selected
boolean nav1_big = true;    // is big or small increment selected
boolean nav2_big = true;    // is big or small increment selected
boolean obs1_sel = true;    // is nav1 or nav2 obs selected

// setup function is called once when Teensy boots up
void setup_pushbutton()
{
    // initialize hardware
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(13, INPUT_PULLUP);
    pinMode(14, INPUT_PULLUP);
    pinMode(15, INPUT_PULLUP);
    pinMode(16, INPUT_PULLUP);
    pinMode(26, INPUT_PULLUP);
    pinMode(27, INPUT_PULLUP);
    pinMode(33, INPUT_PULLUP);
    pinMode(34, INPUT_PULLUP);
    pinMode(35, INPUT_PULLUP);
    pinMode(36, INPUT_PULLUP);
    pinMode(37, INPUT_PULLUP);
    pinMode(44, INPUT_PULLUP);
    pinMode(45, INPUT_PULLUP);

    pinMode(6, OUTPUT);
    digitalWrite(6, HIGH);
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);

    // configure the X-plane variables
    COM1StdbyFlip = XPlaneRef("sim/radios/com1_standy_flip");
    COM2StdbyFlip = XPlaneRef("sim/radios/com2_standy_flip");
    NAV1StdbyFlip = XPlaneRef("sim/radios/nav1_standy_flip");
    NAV2StdbyFlip = XPlaneRef("sim/radios/nav2_standy_flip");
    ADFStdbyFlip = XPlaneRef("sim/radios/adf1_standy_flip");
    ADFHundredsUp = XPlaneRef("sim/radios/stby_adf1_hundreds_up");
    ADFTensUp = XPlaneRef("sim/radios/stby_adf1_tens_up");
    ADFOnesUp = XPlaneRef("sim/radios/stby_adf1_ones_up");
    TransponderThousandsUp = XPlaneRef("sim/transponder/transponder_thousands_up");
    TransponderHundredsUp = XPlaneRef("sim/transponder/transponder_hundreds_up");
    TransponderTensUp = XPlaneRef("sim/transponder/transponder_tens_up");
    TransponderOnesUp = XPlaneRef("sim/transponder/transponder_ones_up");
    DMESelectSource =  XPlaneRef("sim/cockpit2/radios/actuators/DME_slave_source");
    DMESelectSource = 0;
}

// loop functions is called repeatedly as long as Teensy is powered up
void loop_pushbutton()
{
    // gets state of encoder pushbuttons and sets
    // corresponding booleans acordingly
    if (shift_1.update())
        if (shift_1.fallingEdge())
            com1_big = !com1_big;
    if (shift_2.update())
        if (shift_2.fallingEdge())
            nav1_big = !nav1_big;
    if (shift_3.update())
        if (shift_3.fallingEdge())
            com2_big = !com2_big;
    if (shift_4.update())
        if (shift_4.fallingEdge())
            nav2_big = !nav2_big;
    if (OBSsel_6.update())
        if (OBSsel_6.fallingEdge())
            obs1_sel = !obs1_sel;

    // gets state of Act/Stdby buttons and
    // sends command to simulator
    if (act_stdby_1.update())
        if (act_stdby_1.fallingEdge())
            COM1StdbyFlip.once();
    if (act_stdby_2.update())
        if (act_stdby_2.fallingEdge())
            NAV1StdbyFlip.once();
    if (act_stdby_3.update())
        if (act_stdby_3.fallingEdge())
            COM2StdbyFlip.once();
    if (act_stdby_4.update())
        if (act_stdby_4.fallingEdge())
            NAV2StdbyFlip.once();
    if (act_stdby_5.update())
        if (act_stdby_5.fallingEdge())
            ADFStdbyFlip.once();

    // gets state of ADF ciffer buttons and
    // sends commands to simulator
    if (adf_1.update())
        if (adf_1.fallingEdge())
            ADFOnesUp.once();
    if (adf_10.update())
        if (adf_10.fallingEdge())
            ADFTensUp.once();
    if (adf_100.update())
        if (adf_100.fallingEdge())
            ADFHundredsUp.once();

    // gets state of Tranponder buttons and
    // sends commands to simulator
    if (trans_1.update())
        if (trans_1.fallingEdge())
            TransponderOnesUp.once();
    if (trans_10.update())
        if (trans_10.fallingEdge())
            TransponderTensUp.once();
    if (trans_100.update())
        if (trans_100.fallingEdge())
            TransponderHundredsUp.once();
    if (trans_1000.update())
        if (trans_1000.fallingEdge())
            TransponderThousandsUp.once();

    // gets state of DME selection buttons
    // sets LEDs and sends commands to simulator
    if (dmeNAV1.update())
        if (dmeNAV1.fallingEdge())
        {
            DMESelectSource = 0;
            digitalWrite(6, HIGH);
            digitalWrite(12, LOW);
        }
    if (dmeNAV2.update())
        if (dmeNAV2.fallingEdge())
        {
            DMESelectSource = 1;
            digitalWrite(6, LOW);
            digitalWrite(12, HIGH);
        }

}



#endif // PUSHBUTTON_H
