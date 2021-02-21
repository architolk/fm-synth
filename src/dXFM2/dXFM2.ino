/*
*  dXFM2 synthesizer main module
*
*  this is the main module for the dXFM2 synthesizer
*  the individual IC's are controled from submodules
*  this module will set the pinout and start of the SPI and I2C libraries
*
*/
#include "SPI.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/Dungeon9pt7b.h>
#include <Fonts/Dungeon12pt7b.h>

#define NO_ERROR 0
#define ERR_UNIT 1
#define ERR_DUMP 2
#define ERR_LOAD 3

//Go back to the overview display after 2 seconds
#define DISPLAYPERIOD 2000

//Set this to the targetted serial interface
//Serial = USB serial, for debugging
//Serial1 = XFM2 serial, for real-live purpose
#define HWSERIAL Serial1

//Need to put the typedef here, for function's sake...
typedef struct {
  uint8_t unit; //the unit that is selected
  uint16_t param; //the parameter that is selected
} param_type;

//Typedef for envelope
//dly = time for the envelope to start
//r1 = rate of the attack phase (0 = slow, 255 = fast)
//r2 = rate of the decay-1 phase
//r3 = rate of the decay-2 phase
//r4 = rate of the release-1 phase
//r5 = rate of the release-2 phase
//l0 = level at start of the envelope
//l1 = level after the attack phase
//l2 = level after the decay-1 phase
//l3 = level after the decay-2 phase (= sustain level)
//l4 = level after the release-1 phase
//l5 = level after the release-2 phase (= end level)
typedef struct {
  uint8_t rate[6];  //dly, r1, r2, r3, r4, r5
  uint8_t level[6]; //l0, l1, l2, l3, l4, l5
} env_type;

const uint8_t MAXPIN_LOAD = 10; //LOAD pin for Teensy of the MAX7219CNG chip

//Default menu: OSC of unit 1, Volume
uint8_t greenSelect = 2;
uint8_t blueSelect = 0;
uint8_t operatorSelect = 0; //Selected operator, often the same as operator used, except for envelopes
uint8_t operatorUsed = 0; //Operator actually used
uint8_t toggleMode = 0; //Sets the toggle mode
uint8_t patchSelect = 0; //The active patch

bool overviewMode = true; //Sets the overview mode (extra information, is temporarilly set to false whenever you hit a button)
unsigned long lastChange = 0; //Sets the time when you last hit a button

void setup() {
  setupParams();

  //We begin with the LEDs, splash them and continu with the OLED screens
  pinMode(MAXPIN_LOAD, OUTPUT); //MAXPIN_LOAD is defined in the submodule
  SPI.begin();
  setupLEDButtons(); //setup instructions for the LED buttons
  splashLEDs(); //default splash screen for the LEDs

  //Next, we initialize the MCP23017 for the encoders
  Wire.begin();
  setupEncoders();

  //Next, we splash the OLED screens
  setupScreens();
  splashScreens();

  //Start serial interface
  HWSERIAL.begin(500000);

  delay(1000); //one seconds splash screen

  //Start communication with the XFM2
  uint8_t errorCode = initXFM2();
  if (errorCode>0) {
    showError(errorCode);
    delay(2000);
  }

  initLEDs(); //Initialize LEDs to startup position
  initScreens(); //Initialize OLED screens to startup position

  doMenuChange(); //Set OLED screens to current menu
}

void loop() {
  scanLEDButtons();
  delay(50); //Some delay to mitigate bouncing, should be done with timer and not a delay - whatever for now!
  if (millis() - lastChange > DISPLAYPERIOD) {
    //Some time has past
    if (!overviewMode) {
      //overviewMode wasn't active, so make it active and show the new screens (if any)
      overviewMode = true;
      doMenuChange();
    }
  }
}

//Reset the last change, so the overviewmode will be disabled for the DISPLAYPERIOD
void resetLastChange() {
  overviewMode = false;
  lastChange = millis();
}

//A LED button was pressed, respond!
void doLEDButtonPressed(uint8_t row, uint8_t col, uint8_t menu, uint8_t btn) {
  resetLastChange();
  if (menu==7) {
    //Blue menu toggle
    toggleLEDRow(row,col,menu,btn);
    if (blueSelect==btn) {
      toggleMode = 1-toggleMode; //Same blue button selected, so toggle
    } else {
      toggleMode = 0; //Different button selected, so toggle to mode 0
    }
    blueSelect = btn;
    //Respond to menu change
    doMenuChange();
  } else {
    if (menu>7) {
      //Green menu toggle (a bit of a hack: buttons might not have the correct value, but we don't use that anyway...)
      clearLEDRow(5);
      clearLEDRow(7);
      toggleLEDRow(row,col,menu,btn);
      //Respond to menu change
      toggleMode = 0;
      greenSelect = btn;
      doMenuChange();
    } else {
      //Operator matrix set/unset
      toggleLED(row,col,menu,btn);
      toggleLEDParamValueBit(menu,btn);
      if (menu==6) {
        //Do change for carriers
        activateChange(5,0,0,btn,0);
      } else {
        //Do change for modulators
        activateChange(5,0,0,menu,0);
      }
    }
  }
}

//An encoder was used, respond!
void doEncoderUsed(uint8_t encoder, bool clicked, uint8_t value) {
  resetLastChange();
  if (encoder<7) {
    uint8_t paramType = getParamType(greenSelect,blueSelect,operatorSelect,encoder,0);
    if (paramType==3) {
      if (clicked) {
        uint8_t oldSelected = operatorSelect;
        operatorSelect = encoder;
        showDisplay(oldSelected); //Reset the display that is no longer selected
        for (uint8_t op=0; op<7; op++) {
          //Set encoder to the correct value for that operator
          setEncoderValue(op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0));
        }
      } else {
        operatorUsed = encoder;
        setParamValue(greenSelect,blueSelect,operatorSelect,encoder,0,value);
        activateChange(greenSelect,blueSelect,operatorSelect,encoder,0);
      }
    } else {
      if (paramType==2) {
        if (clicked) {
          operatorUsed = encoder;
          operatorSelect = encoder;
          toggleParamValueBit(greenSelect,blueSelect,operatorSelect,encoder,1,encoder);
          activateChange(greenSelect,blueSelect,operatorSelect,encoder,1);
        } else {
          operatorUsed = encoder;
          operatorSelect = encoder;
          setParamValue(greenSelect,blueSelect,operatorSelect,encoder,0,value);
          activateChange(greenSelect,blueSelect,operatorSelect,encoder,0);
        }
      } else {
        operatorUsed = encoder;
        operatorSelect = encoder;
        setParamValue(greenSelect,blueSelect,operatorSelect,encoder,toggleMode,value);
        activateChange(greenSelect,blueSelect,operatorSelect,encoder,toggleMode);
      }
    }
    showDisplay(operatorSelect);
  } else {
    if (encoder==9) {
      if (clicked) {
        //Laden van een programma
        patchSelect = value;
        if (xfm2LoadPatch(patchSelect)) {
          if (xfm2GetActiveProgram(0)) {
            updateLEDs();
            doMenuChange();
          } else {
            showError(ERR_DUMP);
          }
        } else {
          showError(ERR_LOAD);
        }
      } else {
        //Toggle door de programma's heen
        showPatchMenu(value);
      }
    } else {
      if (encoder==8) {
        if (clicked) {
          //Debug demo
          startDemo();
        }
      }
    }
  }
}

//Starts the serial communication to activate a change
//Maybe this can be part of setParamValue and toggleParamValueBit, but for now...
void activateChange(uint8_t green, uint8_t blue, uint8_t selOp, uint8_t usedOp, uint8_t toggle) {
  param_type param = getParam(green,blue,selOp,usedOp,toggle);
  //showDebug(param.param);
  xfm2SetParameter(param.param,getParamValueQuick(param));
}

// Menu change, all screens are affected!
void doMenuChange() {
  operatorUsed = 0; //Reset operator used
  for (uint8_t op=0; op<7; op++) {
    //Set encoder to the correct value for that operator
    setEncoderValue(op,getParamValue(greenSelect,blueSelect,operatorSelect,op,toggleMode));
    setEncoderMax(op,getParamMax(greenSelect,blueSelect,operatorSelect,op,toggleMode));
    showDisplay(op);
  }
}

void startDemo() {
  for (uint8_t screen=0; screen<7; screen++) {
    showScreenBorder(screen);
  }
}
