// Cockpit for X-Plane using Teensy++ 2.0 Boards
//
// Version 0.01
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
#include "encoder.h"
#include "pushbutton.h"
#include "flipswitch.h"
#include "display.h"

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
    // normally the first step in loop() should update from X-Plane
    FlightSim.update();

    // call loop functions of the
    // different modules
    loop_display();
    loop_encoder();
    loop_flipswitch();
    loop_pushbutton();


  // read the rotary encoder, if it's changed, write to NavFrequencyHz
  long enc = wheel.read();
  if (enc != encoder_prev) {
    NavFrequencyHz = NavFrequencyHz + (enc - encoder_prev);
    encoder_prev = enc;
    update_lcd(NavFrequencyHz);
    inactivityTimeout = 0;   // reset the inactivity timeout
  }

}

