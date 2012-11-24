#ifndef DISPLAY_H
#define DISPLAY_H


// for syntax highlighting
#include "usb_api.h"
#include "LiquidCrystal.h"

// includes
#include "pushbutton.h"

// hardware objects
LiquidCrystal lcd(20, 21, 22, 23, 24, 25);  // LCD Pins RS, Enable, D4 to D7


// X-Plane objects
FlightSimInteger COM1FrequencyHz;
FlightSimInteger COM1StdbyFreqencyHz;
FlightSimInteger COM2FrequencyHz;
FlightSimInteger COM2StdbyFrequencyHz;
FlightSimInteger NAV1FrequencyHz;
FlightSimInteger NAV1StdbyFrequencyHz;
FlightSimInteger NAV2FrequencyHz;
FlightSimInteger NAV2StdbyFrequencyHz;
FlightSimInteger ADFFrequencyHz;
FlightSimInteger ADFStdbyFrequencyHz;
FlightSimInteger TransponderCode;

// variables
boolean display_init = false;
boolean display_wait = false;

// declarations
void update_lcd(long var);

// setup function ist called once when Teensy boots
void setup_display()
{
    // initialize lcd hardware
    lcd.begin(20, 4);                   // LCD rows and columns
    lcd.clear();                        // clear the LCD
    lcd.noCursor();                     // do not display cursor

    // display startup message
    lcd.setCursor(3, 0);
    lcd.print("RADIO   PANEL");
    delay(1000);
    lcd.setCursor(8, 1);
    lcd.print("for");
    delay(1000);
    lcd.setCursor(6, 2);
    lcd.print("X-plane");
    delay(1000);
    lcd.setCursor(3, 3);
    lcd.print("Version  0.97");
    delay(10000);

    // print fixed labels on lcd-display
    lcd.setCursor(0,0);                 // set cursor to x/y position
    lcd.print("COM1");                  // print to lcd
    lcd.setCursor(0,1);                 // set cursor to x/y position
    lcd.print("COM2");                  // print to lcd
    lcd.setCursor(0,2);                 // set cursor to x/y position
    lcd.print("NAV1");                  // print to lcd
    lcd.setCursor(0,3);                 // set cursor to x/y position
    lcd.print("ADF");                   // print to lcd
    lcd.setCursor(10,3);                // set cursor to x/y position
    lcd.print("TRANS");                 // print to lcd
    lcd.setCursor(12,0);                // set cursor to x/y position
    lcd.print("*");                     // print to lcd
    lcd.setCursor(12,1);                // set cursor to x/y position
    lcd.print("*");                     // print to lcd
    lcd.setCursor(12,2);                // set cursor to x/y position
    lcd.print("*");                     // print to lcd



    // configure the X-Plane variables
    COM1FrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/com1_frequency_hz");
    COM1StdbyFreqencyHz = XPlaneRef("sim/cockpit2/radios/actuators/com1_standby_frequency_hz");
    COM1FrequencyHz.onChange(update_lcd);
    COM1StdbyFreqencyHz.onChange(update_lcd);

    COM2FrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/com2_frequency_hz");
    COM2StdbyFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/com2_standby_frequency_hz");
    COM2FrequencyHz.onChange(update_lcd);
    COM2StdbyFrequencyHz.onChange(update_lcd);

    NAV1FrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/nav1_frequency_hz");
    NAV1StdbyFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/nav1_standby_frequency_hz");
    NAV1FrequencyHz.onChange(update_lcd);
    NAV1StdbyFrequencyHz.onChange(update_lcd);

    NAV2FrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/nav2_frequency_hz");
    NAV2StdbyFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/nav2_standby_frequency_hz");
    NAV2FrequencyHz.onChange(update_lcd);
    NAV2StdbyFrequencyHz.onChange(update_lcd);

    ADFFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/adf1_frequency_hz");
    ADFStdbyFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/adf1_standby_frequency_hz");
    ADFFrequencyHz.onChange(update_lcd);
    ADFStdbyFrequencyHz.onChange(update_lcd);

    TransponderCode = XPlaneRef("sim/cockpit2/radios/actuators/transponder_code");
    TransponderCode.onChange(update_lcd);

}

// loop function is repeatedly called as long as Teensy is powered up
void loop_display()
{
    if (FlightSim.isEnabled())                  // X-plane running?
    {
        display_wait = false;
        if (display_init == false)              // only once to prevent flickering!
        {
            lcd.clear();                        // clear display

            // print fixed labels on lcd-display
            lcd.setCursor(0,0);                 // set cursor to x/y position
            lcd.print("COM1");                  // print to lcd
            lcd.setCursor(0,1);                 // set cursor to x/y position
            lcd.print("COM2");                  // print to lcd
            lcd.setCursor(0,2);                 // set cursor to x/y position
            lcd.print("NAV1");                  // print to lcd
            lcd.setCursor(0,3);                 // set cursor to x/y position
            lcd.print("ADF");                   // print to lcd
            lcd.setCursor(10,3);                // set cursor to x/y position
            lcd.print("TRANS");                 // print to lcd
            lcd.setCursor(12,0);                // set cursor to x/y position
            lcd.print("*");                     // print to lcd
            lcd.setCursor(12,1);                // set cursor to x/y position
            lcd.print("*");                     // print to lcd
            lcd.setCursor(12,2);                // set cursor to x/y position
            lcd.print("*");                     // print to lcd

            display_init = true;                // display is initialized
        }

    }
    else
    {
        display_init = false;
        if (display_wait == false)          // only once to prevent flickering!
        {
            lcd.clear();
            // display waiting message
            lcd.setCursor(4, 0);                // set cursor to x/y position
            lcd.print("Waiting for");                     // print to lcd
            lcd.setCursor(5, 1);                // set cursor to x/y position
            lcd.print("X-plane &");                     // print to lcd
            lcd.setCursor(3, 2);                // set cursor to x/y position
            lcd.print("Teensy-plugin");                     // print to lcd
            lcd.setCursor(4, 3);                // set cursor to x/y position
            lcd.print("to connect");                     // print to lcd

            display_wait = true;
        }

    }

}

void update_lcd(long var)
{
    // COM1
    lcd.setCursor(5, 0);
    lcd.print(COM1FrequencyHz);
    lcd.setCursor(13, 0);
    lcd.print(COM1StdbyFreqencyHz);
    if (com1_big)
    {
        lcd.setCursor(12, 0);
        lcd.print("*");
        lcd.setCursor(19, 0);
        lcd.print(" ");
    }
    else
    {
        lcd.setCursor(12, 0);
        lcd.print(" ");
        lcd.setCursor(19, 0);
        lcd.print("*");
    }

    //COM2
    lcd.setCursor(5, 1);
    lcd.print(COM2FrequencyHz);
    lcd.setCursor(13, 1);
    lcd.print(COM2StdbyFrequencyHz);
    if (com2_big)
    {
        lcd.setCursor(12, 1);
        lcd.print("*");
        lcd.setCursor(19, 1);
        lcd.print(" ");
    }
    else
    {
        lcd.setCursor(12, 1);
        lcd.print(" ");
        lcd.setCursor(19, 1);
        lcd.print("*");
    }

    //NAV1
    lcd.setCursor(5, 2);
    lcd.print(NAV1FrequencyHz);
    lcd.setCursor(13, 2);
    lcd.print(NAV1StdbyFrequencyHz);
    if (nav1_big)
    {
        lcd.setCursor(12, 2);
        lcd.print("*");
        lcd.setCursor(19, 2);
        lcd.print(" ");
    }
    else
    {
        lcd.setCursor(12, 2);
        lcd.print(" ");
        lcd.setCursor(19, 2);
        lcd.print("*");
    }

    //ADF
    lcd.setCursor(4, 3);
    lcd.print(ADFFrequencyHz);

    //Transponder
    lcd.setCursor(16, 3);
    lcd.print (TransponderCode);

}

#endif // DISPLAY_H
