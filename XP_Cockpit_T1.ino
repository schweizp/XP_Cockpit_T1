// Cockpit for X-Plane using Teensy++ 2.0 Boards
//
// Version 0.97
// by Philemon Schweizer
//
// Teensy Board No.1
// LCD 4x20
// COM 1 u. 2
// NAV 1
// ADF
// Transponder
// DME
// 
//


// for syntax highlighting purposes
#include "usb_api.h"

// include the different specialized coding parts
#include "display.h"
#include "pushbutton.h"
#include "encoder.h"
#include "flipswitch.h"


#include <elapsedMillis.h>
#include <Bounce.h>
#include <Encoder.h>
#include <LiquidCrystal.h>



// setup runs once, when Teensy boots.
void setup()
{
    // call setup functions of the
    // different modules
    setup_display();
    setup_encoder();
    setup_flipswitch();
    setup_pushbutton();
}

// loop runs repetitively, as long as Teensy is powered up
void loop()
{
    // variables
    elapsedMillis time;
    unsigned long old_time;
    unsigned long diff;

    // normally the first step in loop() should update from X-Plane
    FlightSim.update();

    // call loop functions of the
    // different modules
    loop_display();
    loop_encoder();
    loop_flipswitch();
    loop_pushbutton();

    // timing message
    diff = time - old_time;
    old_time = time;
    lcd.setCursor(0,3);
    lcd.print(diff);
}

