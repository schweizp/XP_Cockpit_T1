// Cockpit for X-Plane using Teensy++ 2.0 Boards
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

#include "usb_api.h"        // for syntax highlighting purposes

#include <Bounce.h>
#include <Encoder.h>
#include <LiquidCrystal.h>

// hardware objects, for accessing the buttons, switches, rotary encoder and LCD
//
LiquidCrystal lcd(20, 21, 22, 23, 24, 25);  // LCD Pins RS, Enable, D4 to D7
Encoder       wheel_1(0, 27);                      // Encoder COM1 Frequency
Bounce        shift_1(8, 10);                      // shift big to small increment
Bounce        act_stdby_1(9, 10);                  // Active / Stdby button
Encoder       wheel_2(1, 3);                       // Encoder NAV1 Frequency
Bounce        shift_2(36, 10);                     // shift big to small increment
Bounce        act_stdby_2(10, 10);                 // Active / Stdby button
Encoder       wheel_3(2, 4);                       // Encoder COM2 frequency
Bounce        shift_3(26, 10);                     // shift big to small increment
Bounce        act_stdby_3(11, 10);                 // Active / Stdby button
Encoder       wheel_5(18, 5);                      // Encoder ADF frequency
Bounce        sel_adf(13, 10);                     // ADF Buttons....
Bounce        sel_bfo(14, 10);
Bounce        act_stdby_5(15, 10);
Bounce        sel_flt(16, 10);                    
Bounce        sel_set(17, 10);
Bounce        tModeOff(28, 10);                    // Transponder rotary switch Mode selector...
Bounce        tModeSby(29, 10);
Bounce        tModeOn(30, 10);
Bounce        tModeAlt(31, 10);
Bounce        tModeTest(32, 10);
Bounce        t_1(33, 10);                         // Transponder ciffer buttons
Bounce        t_2(34, 10);
Bounce        t_3(35, 10);
Bounce        t_4(38, 10);
Bounce        t_5(39, 10);
Bounce        t_6(40, 10);
Bounce        t_7(41, 10);
Bounce        t_0(42, 10);
Bounce        t_Shift(43, 10);
Encoder       wheel_6(19, 7);                      // OBS bearing selector
Bounce        OBSsel_6(37, 10);                    // Select OBS1 or OBS2 
Bounce        dmeNAV1(44, 10);                     // DME mode select buttons
Bounce        dmeNAV2(45, 10);






// X-Plane objects, 3 command refs and 1 data ref
FlightSimInteger COM1FrequencyHz; 
FlightSimInteger COM1StdbyFreqencyHz;
FlightSimCommand COM1StdbyFlip;
FlightSimCommand  COM1CoarseUp;
FlightSimCommand  COM1CoarseDown;
FlightSimCommand  COM1FineUp;
FlightSimCommand  COM1FineDown;
  
  
FlightSimInteger COM2FrequencyHz;
FlightSimInteger COM2StdbyFrequencyHz;
FlightSimCommand  COM2StdbyFlip;
FlightSimCommand  COM2CoarseUp;
FlightSimCommand  COM2CoarseDown;
FlightSimCommand  COM2FineUp;
FlightSimCommand  COM2FineDown;
  
  
FlightSimInteger NAV1FrequencyHz;
FlightSimInteger NAV1StdbyFrequencyHz;
FlightSimCommand  NAV1StdbyFlip;
FlightSimCommand  NAV1CoarseUp;
FlightSimCommand  NAV1CoarseDown;
FlightSimCommand  NAV1FineUp;
FlightSimCommand  NAV1FineDown;
 
  
FlightSimInteger NAV2FrequencyHz;
FlightSimInteger NAV2StdbyFrequencyHz;
FlightSimCommand  NAV2StdbyFlip;
FlightSimCommand  NAV2CoarseUp;
FlightSimCommand  NAV2CoarseDown;
FlightSimCommand  NAV2FineUp;
FlightSimCommand  NAV2FineDown;
  
  
FlightSimInteger ADFFrequencyHz;
FlightSimInteger ADFStdbyFrequencyHz;
FlightSimCommand  ADFStdbyFlip;
FlightSimCommand  ADFHundredsDown;
FlightSimCommand  ADFHundredsUp;
FlightSimCommand  ADFTensDown;
FlightSimCommand  ADFTensUp;
FlightSimCommand  ADFOnesDown;
FlightSimCommand  ADFOnesUp;
  
    
FlightSimInteger TransponderCode;
FlightSimInteger TransponderMode;
FlightSimCommand  TransponderThousandsDown;
FlightSimCommand  TransponderThousandsUp;
FlightSimCommand  TransponderHundredsDown;
FlightSimCommand  TransponderHundredsUp;
FlightSimCommand  TransponderTensDown;
FlightSimCommand  TransponderTensUp;
FlightSimCommand  TransponderOnesDown;
FlightSimCommand  TransponderOnesUp;

  
FlightSimCommand  OBS1Down;
FlightSimCommand  OBS1Up;
FlightSimCommand  OBS2Down;
FlightSimCommand  OBS2Up;
FlightSimCommand  OBSHSIDown;
FlightSimCommand  OBSHSIUp;                         
  
    
FlightSimInteger DMESelectSource;


// variables
long encoder_prev=0;    // for detecting rotary position change
elapsedMillis inactivityTimeout;// an inactivity timeout


// setup runs once, when Teensy boots.
//
void setup() {
  // initialize all hardware

  pinMode(6, OUTPUT);
  pinMode(8, INPUT_PULLUP);              // input pullup mode allows connecting 
  pinMode(9, INPUT_PULLUP);              // input pullup mode allows connecting
  pinMode(10, INPUT_PULLUP);             // to ground, and the chip provide the
  pinMode(11, INPUT_PULLUP);             // required pullup resistor :-)
  pinMode(12, OUTPUT);
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(30, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(36, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(44, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
   
  lcd.begin(20, 4);                            // LCD rows and columns
  
  // print labels to lcd
  lcd.print("nav1:");



  // configure the X-Plane variables
  COM1FrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/com1_frequency_hz");
  COM1StdbyFreqencyHz = XPlaneRef("sim/cockpit2/radios/actuators/com1_standby_frequency_hz");
  COM1StdbyFlip = XPlaneRef("sim/radios/com1_standy_flip");
  COM1CoarseUp =  XPlaneRef("sim/radios/stby_com1_coarse_up");
  COM1CoarseDown = XPlaneRef("sim/radios/stby_com1_coarse_down");
  COM1FineUp = XPlaneRef("sim/radios/stby_com1_fine_up");
  COM1FineDown = XPlaneRef("sim/radios/stby_com1_fine_down");
  COM1FrequencyHz.onChange(update_lcd);
  COM1StdbyFreqencyHz.onChange(update_lcd);
  
  
  COM2FrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/com2_frequency_hz");
  COM2StdbyFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/com2_standby_frequency_hz");
  COM2StdbyFlip = XPlaneRef("sim/radios/com2_standy_flip");
  COM2CoarseUp =  XPlaneRef("sim/radios/stby_com2_coarse_up");
  COM2CoarseDown = XPlaneRef("sim/radios/stby_com2_coarse_down");
  COM2FineUp = XPlaneRef("sim/radios/stby_com2_fine_up");
  COM2FineDown = XPlaneRef("sim/radios/stby_com2_fine_down");
  COM2FrequencyHz.onChange(update_lcd);
  COM2StdbyFrequencyHz.onChange(update_lcd);
  
  
  NAV1FrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/nav1_frequency_hz");
  NAV1StdbyFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/nav1_standby_frequency_hz");
  NAV1StdbyFlip = XPlaneRef("sim/radios/nav1_standy_flip");
  NAV1CoarseUp =  XPlaneRef("sim/radios/stby_nav1_coarse_up");
  NAV1CoarseDown = XPlaneRef("sim/radios/stby_nav1_coarse_down");
  NAV1FineUp = XPlaneRef("sim/radios/stby_nav1_fine_up");
  NAV1FineDown = XPlaneRef("sim/radios/stby_nav1_fine_down");
  NAV1FrequencyHz.onChange(update_lcd);
  NAV1StdbyFrequencyHz.onChange(update_lcd);
  
  
  NAV2FrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/nav2_frequency_hz");
  NAV2StdbyFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/nav2_standby_frequency_hz");
  NAV2StdbyFlip = XPlaneRef("sim/radios/nav2_standy_flip");
  NAV2CoarseUp =  XPlaneRef("sim/radios/stby_nav2_coarse_up");
  NAV2CoarseDown = XPlaneRef("sim/radios/stby_nav2_coarse_down");
  NAV2FineUp = XPlaneRef("sim/radios/stby_nav2_fine_up");
  NAV2FineDown = XPlaneRef("sim/radios/stby_nav2_fine_down");
  NAV2FrequencyHz.onChange(update_lcd);
  NAV2StdbyFrequencyHz.onChange(update_lcd);
  
  
  ADFFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/adf1_frequency_hz");
  ADFStdbyFrequencyHz = XPlaneRef("sim/cockpit2/radios/actuators/adf1_standby_frequency_hz");
  ADFStdbyFlip = XPlaneRef("sim/radios/adf1_standy_flip");
  ADFHundredsDown = XPlaneRef("sim/radios/stby_adf1_hundreds_down");
  ADFHundredsUp = XPlaneRef("sim/radios/stby_adf1_hundreds_up");
  ADFTensDown = XPlaneRef("sim/radios/stby_adf1_tens_down");
  ADFTensUp = XPlaneRef("sim/radios/stby_adf1_tens_up");
  ADFOnesDown = XPlaneRef("sim/radios/stby_adf1_ones_down");
  ADFOnesUp = XPlaneRef("sim/radios/stby_adf1_ones_up");
  ADFFrequencyHz.onChange(update_lcd);
  ADFStdbyFrequencyHz.onChange(update_lcd);
  
    
  TransponderCode = XPlaneRef("sim/cockpit2/radios/actuators/transponder_code");
  TransponderMode = XPlaneRef("sim/cockpit2/radios/actuators/transponder_mode");
  TransponderThousandsDown = XPlaneRef("sim/transponder/transponder_thousands_down");
  TransponderThousandsUp = XPlaneRef("sim/transponder/transponder_thousands_up");
  TransponderHundredsDown = XPlaneRef("sim/transponder/transponder_hundreds_down");
  TransponderHundredsUp = XPlaneRef("sim/transponder/transponder_hundreds_up");
  TransponderTensDown = XPlaneRef("sim/transponder/transponder_tens_down");
  TransponderTensUp = XPlaneRef("sim/transponder/transponder_tens_up");
  TransponderOnesDown = XPlaneRef("sim/transponder/transponder_ones_down");
  TransponderOnesUp = XPlaneRef("sim/transponder/transponder_ones_up");       
  TransponderCode.onChange(update_lcd);
  
  
  OBS1Down = XPlaneRef("sim/radios/obs1_down");
  OBS1Up = XPlaneRef("sim/radios/obs1_up");
  OBS2Down = XPlaneRef("sim/radios/obs2_down");
  OBS2Up = XPlaneRef("sim/radios/obs2_up");
  OBSHSIDown = XPlaneRef("sim/radios/obs_HSI_down");
  OBSHSIUp = XPlaneRef("sim/radios/obs_HSI_up");                         
  
  
  DMESelectSource =  XPlaneRef("sim/cockpit2/radios/actuators/DME_slave_source");

}

// loop runs repetitively, as long as Teensy is powered up
//
void loop() {
  // normally the first step in loop() should update from X-Plane
  FlightSim.update();

  // read the rotary encoder, if it's changed, write to NavFrequencyHz
  long enc = wheel.read();
  if (enc != encoder_prev) {
    NavFrequencyHz = NavFrequencyHz + (enc - encoder_prev);
    encoder_prev = enc;
    update_lcd(NavFrequencyHz);
    inactivityTimeout = 0;   // reset the inactivity timeout
  }

  // read the pushbuttons, and send X-Plane commands when they're pressed
  buttonUp.update();
  buttonDown.update();
  if (buttonUp.fallingEdge()) {
    NavCoarseUp = 1;
    inactivityTimeout = 0;
  }
  if (buttonUp.risingEdge()) {
    NavCoarseUp = 0;
  }
  if (buttonDown.fallingEdge()) {
    NavCoarseDown = 1;
    inactivityTimeout = 0;
  }
  if (buttonDown.risingEdge()) {
    NavCoarseDown = 0;
  }

  // if there's no user activity for 2 seconds, send the NavFineUp.
  // admittedly this is not very useful, but it's meant to demonstrate
  // possibility of automated actions in addition to driving everything
  // directly from physical user inputs.
  if (inactivityTimeout > 2000) {
    NavFineUp.once();
    inactivityTimeout = 0;
  }
}

// write a number onto the LCD, first row, starting at 6th column
void update_lcd(long val)
{
  lcd.setCursor(6, 0);
  lcd.print(val);
  lcd.print("  ");
}
