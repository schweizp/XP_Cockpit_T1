#ifndef ENCODER_H
#define ENCODER_H

// defines
#define RESOLUTION 4

// for syntax highlighting purposes
#include "usb_api.h"
#include <Encoder.h>

// includes
#include "pushbutton.h"
#include "display.h"

// hardware objects
Encoder     wheel_1(0, 27);     // Encoder COM1 frequency
Encoder     wheel_2(1, 4);      // Encoder NAV1 frequency
Encoder     wheel_3(2, 5);      // Encoder COM2 frequency
Encoder     wheel_4(3, 7);      // Encoder NAV2 frequency
Encoder     wheel_5(18, 38);    // Encoder ADF frequency
Encoder     wheel_6(19, 39);    // Encoder OBS bearing

// X-Plane objects
FlightSimCommand  COM1CoarseUp;
FlightSimCommand  COM1CoarseDown;
FlightSimCommand  COM1FineUp;
FlightSimCommand  COM1FineDown;

FlightSimCommand  COM2CoarseUp;
FlightSimCommand  COM2CoarseDown;
FlightSimCommand  COM2FineUp;
FlightSimCommand  COM2FineDown;

FlightSimCommand  NAV1CoarseUp;
FlightSimCommand  NAV1CoarseDown;
FlightSimCommand  NAV1FineUp;
FlightSimCommand  NAV1FineDown;

FlightSimCommand  NAV2CoarseUp;
FlightSimCommand  NAV2CoarseDown;
FlightSimCommand  NAV2FineUp;
FlightSimCommand  NAV2FineDown;

FlightSimCommand  OBS1Down;
FlightSimCommand  OBS1Up;
FlightSimCommand  OBS2Down;
FlightSimCommand  OBS2Up;
FlightSimCommand  OBSHSIDown;
FlightSimCommand  OBSHSIUp;

// variables
long com1_enc = 0;
long com2_enc = 0;
long nav1_enc = 0;
long nav2_enc = 0;
long adf_enc = 0;
long obs_enc = 0;

long enc1 = 0;
long enc2 = 0;
long enc3 = 0;
long enc4 = 0;
long enc5 = 0;
long enc6 = 0;

// setup function is called once when Teensy boots up
void setup_encoder()
{
    // configure the X-Plane variables
    COM1CoarseUp =  XPlaneRef("sim/radios/stby_com1_coarse_up");
    COM1CoarseDown = XPlaneRef("sim/radios/stby_com1_coarse_down");
    COM1FineUp = XPlaneRef("sim/radios/stby_com1_fine_up");
    COM1FineDown = XPlaneRef("sim/radios/stby_com1_fine_down");

    COM2CoarseUp =  XPlaneRef("sim/radios/stby_com2_coarse_up");
    COM2CoarseDown = XPlaneRef("sim/radios/stby_com2_coarse_down");
    COM2FineUp = XPlaneRef("sim/radios/stby_com2_fine_up");
    COM2FineDown = XPlaneRef("sim/radios/stby_com2_fine_down");

    NAV1CoarseUp =  XPlaneRef("sim/radios/stby_nav1_coarse_up");
    NAV1CoarseDown = XPlaneRef("sim/radios/stby_nav1_coarse_down");
    NAV1FineUp = XPlaneRef("sim/radios/stby_nav1_fine_up");
    NAV1FineDown = XPlaneRef("sim/radios/stby_nav1_fine_down");

    NAV2CoarseUp =  XPlaneRef("sim/radios/stby_nav2_coarse_up");
    NAV2CoarseDown = XPlaneRef("sim/radios/stby_nav2_coarse_down");
    NAV2FineUp = XPlaneRef("sim/radios/stby_nav2_fine_up");
    NAV2FineDown = XPlaneRef("sim/radios/stby_nav2_fine_down");

    OBS1Down = XPlaneRef("sim/radios/obs1_down");
    OBS1Up = XPlaneRef("sim/radios/obs1_up");
    OBS2Down = XPlaneRef("sim/radios/obs2_down");
    OBS2Up = XPlaneRef("sim/radios/obs2_up");
    OBSHSIDown = XPlaneRef("sim/radios/obs_HSI_down");
    OBSHSIUp = XPlaneRef("sim/radios/obs_HSI_up");

}

// loop function is called repeatedly as long as Teensy is powered
void loop_encoder()
{

    // read COM1 encoder and send
    // commands to simulator
    enc1 = wheel_1.read();
    if (enc1 > com1_enc + RESOLUTION)
    {
        if (com1_big)
            COM1CoarseUp.once();
        else
            COM1FineUp.once();
        com1_enc = enc1;
    }
    else if (enc1 < com1_enc - RESOLUTION)
    {
        if (com1_big)
            COM1CoarseDown.once();
        else
            COM1FineDown.once();
        com1_enc = enc1;
    }
    // read COM2 encoder and send
    // commands to simulator
    enc3 = wheel_3.read();
    if (enc3 > com2_enc + RESOLUTION)
    {
        if (com2_big)
            COM2CoarseUp.once();
        else
            COM2FineUp.once();
        com2_enc = enc3;

    }
    else if (enc3 < com2_enc - RESOLUTION)
    {
        if (com2_big)
            COM2CoarseDown.once();
        else
            COM2FineDown.once();
        com2_enc = enc3;

    }
    // read NAV1 encoder and send
    // commands to simulator
    enc2 = wheel_2.read();
    if (enc2 > nav1_enc + RESOLUTION)
    {
        if (nav1_big)
            NAV1CoarseUp.once();
        else
            NAV1FineUp.once();
        nav1_enc = enc2;
    }
    else if (enc2 < nav1_enc - RESOLUTION)
    {
        if (nav1_big)
            NAV1CoarseDown.once();
        else
            NAV1FineDown.once();
        nav1_enc = enc2;
    }
    // read NAV2 encoder and send
    // commands to simulator
    enc4 = wheel_4.read();
    if (enc4 > nav2_enc + RESOLUTION)
    {
        if (nav2_big)
            NAV2CoarseUp.once();
        else
            NAV2FineUp.once();
        nav2_enc = enc4;
    }
    else if (enc4 < nav2_enc - RESOLUTION)
    {
        if (nav2_big)
            NAV2CoarseDown.once();
        else
            NAV2FineDown.once();
        nav2_enc = enc4;
    }
    // read OBS encoder and send
    // commands to simulator
    enc6 = wheel_6.read();
    if (enc6 > obs_enc + RESOLUTION)
    {
        if (obs1_sel)
        {
            OBS1Up.once();
            OBSHSIUp.once();
        }
        else
            OBS2Up.once();
        obs_enc = enc6;

    }
    else if (enc6 < obs_enc - RESOLUTION)
    {
        if (obs1_sel)
        {
            OBS1Down.once();
            OBSHSIDown.once();
        }
        else
            OBS2Down.once();
        obs_enc = enc6;
    }

}


#endif // ENCODER_H
