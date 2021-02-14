/*
*  Module for the LED buttons
*
*  this module is about controlling the MAX7219CNG IC
*  and the button switching via six analog inputs
*
*/

//MAX7219CNG register addresses
const uint16_t MAXOP_DIGIT0 = 1;
const uint16_t MAXOP_DECODEMODE = 9;
const uint16_t MAXOP_INTENSITY = 10;
const uint16_t MAXOP_SCANLIMIT = 11;
const uint16_t MAXOP_SHUTDOWN = 12;
const uint8_t MAXVAL_OPERATIONAL = 1;
const uint8_t MAXVAL_NONE = 0;

//Current values of the MAX7219CNG row registers (one for every row)
uint8_t rows[8] = {0,0,0,0,0,0,0,0};

// Mapping from the analog inputs to the LEDs and the menu that is controlled
typedef struct {
  uint8_t row; //row of the LED
  uint8_t col; //col of the LED
  uint8_t menu; //Menu (0-5 = operators, 6 = output, 7 = blue menu, 8 = synth A + master, 9 = synth B)
  uint8_t btn; //Button (0-5 = oerators for menu 0-6, 0-5 = selected item for menu 7-9)
} map_type;
const map_type BTNMAP[6][9] PROGMEM = {
  {{0,2,7,5},{0,0,7,4},{0,4,7,3},{0,5,7,2},{0,6,7,1},{0,1,7,0},{7,5,9,5},{7,5,9,5},{7,5,9,5}} // {7,5,9,5} means: no led
  ,{{1,2,5,0},{1,0,5,1},{1,1,5,2},{1,6,5,3},{1,5,5,4},{7,5,9,5},{7,5,9,5},{7,5,9,5},{7,5,9,5}}
  ,{{2,0,6,5},{2,2,6,4},{2,4,6,3},{2,1,6,2},{2,6,6,1},{2,5,6,0},{7,5,9,5},{7,5,9,5},{7,5,9,5}}
  ,{{6,0,0,1},{6,2,0,2},{6,4,0,3},{6,1,0,4},{6,6,0,5},{3,6,1,5},{3,1,1,4},{3,4,1,3},{3,2,1,2}}
  ,{{4,6,4,5},{4,2,3,4},{4,1,3,5},{4,5,2,5},{4,0,2,4},{4,4,2,3},{7,5,9,5},{7,5,9,5},{7,5,9,5}}
  ,{{5,2,8,0},{5,0,8,1},{5,4,8,2},{5,6,8,3},{5,1,8,4},{7,6,9,3},{7,4,9,2},{7,0,9,1},{7,2,9,0}}
};

// Mapping from menu back to buttons
typedef struct {
  uint8_t row; //row of the LED
  uint8_t col; //col of the LED
} menumap_type;
const menumap_type BTNMENUMAP[7][6] PROGMEM = {
  {{0,0},{6,0},{6,2},{6,4},{6,1},{6,6}}, //{0,0} means: no led for this combination
  {{0,0},{0,0},{3,2},{3,4},{3,1},{3,6}},
  {{0,0},{0,0},{0,0},{4,4},{4,0},{4,5}},
  {{0,0},{0,0},{0,0},{0,0},{4,2},{4,1}},
  {{0,0},{0,0},{0,0},{0,0},{0,0},{4,6}},
  {{1,2},{1,0},{1,1},{1,6},{1,5},{0,0}},
  {{2,5},{2,6},{2,1},{2,4},{2,2},{2,0}}
}

// Current value of a panel's analog output
uint8_t panelvalue[6] = {0,0,0,0,0,0};

// Current state of the buttons, organized for menu's and btn's
// For example: buttons[7][0] is the topmost button of the blue menu
bool buttons[10][6];

void setupLEDButtons() {
  //set all button states to "false"
  for (uint8_t menu=0; menu<10; menu++) {
    for (uint8_t btn=0; btn<6; btn++) {
      buttons[menu][btn] = false;
    }
  }
  //Initialize the MAX7219CNG IC
  sendData(MAXOP_SHUTDOWN, MAXVAL_OPERATIONAL);
  sendData(MAXOP_DECODEMODE, MAXVAL_NONE);
  sendData(MAXOP_SCANLIMIT, 7); // Not needed? All rows are active!
  sendData(MAXOP_INTENSITY, 10); // Default intensity, can be overriden

  //Clear LEDs (the MAX might light up some LEDs at startup)
  clearLEDs();
}

void splashLEDs() {
  setLED(0,1,true); //Volume LED on
  setLED(0,2,true); //Level LED on
  setLED(5,1,true); //Master LED on
}

void initLEDs() {
  toggleLEDRow(0,1,7,0); //Volume button selected
  toggleLEDRow(5,4,8,2); //Operator of synth A selected
/*
  doLEDButtonPressed(0,1,7,0); //Volume button selected
  doLEDButtonPressed(5,4,8,2); //Operator of synth A selected
*/
}

void scanLEDButtons() {
  uint8_t p[6] = {0,0,0,0,0,0};
  p[0] = (analogRead(A9)+85)/171; //Range between 0 and 6 (six buttons on pannel 1, 0 means no button pressed)
  p[1] = (analogRead(A8)+102)/205; //Range between 0 and 5 (five buttons on panel 2)
  p[2] = (analogRead(A3)+85)/171; //Range between 0 and 6 (six buttons on panel 3)
  p[3] = (analogRead(A6)+57)/114; //Range between 0 and 9 (nine buttons on panel 4)
  p[4] = (analogRead(A7)+85)/171; //Range between 0 and 6 (six buttons on panel 5)
  p[5] = (analogRead(A2)+57)/114; //Range between 0 and 9 (nine buttons on panel 6)
  for (int panel=0; panel<6; panel++) {
    if (panelvalue[panel]!=p[panel]) {
      if (panelvalue[panel]==0) {
        //Button down
        //What will happen, depends on the implementation of doLEDButtonPressed in the main module
        doLEDButtonPressed(BTNMAP[panel][p[panel]-1].row,BTNMAP[panel][p[panel]-1].col,BTNMAP[panel][p[panel]-1].menu,BTNMAP[panel][p[panel]-1].btn);
      }
      panelvalue[panel]=p[panel];
    }
  }
}

//Second toggle function, but without need to pass row and col
void toggleLED2(uint8_t menu, uint8_t btn) {
  buttons[menu][btn] = !buttons[menu][btn];
  setLED(BTNMENUMAP[menu][btn].row,BTNMENUMAP[menu][btn].col,buttons[menu][btn]);
}

//Function to toggle one particular LED (all other LEDs remain the same state)
void toggleLED(uint8_t row, uint8_t col, uint8_t menu, uint8_t btn) {
  buttons[menu][btn] = !buttons[menu][btn];
  setLED(row,col,buttons[menu][btn]);
}

//Function to toggle an entire row (like radio buttons)
void toggleLEDRow(uint8_t row, uint8_t col, uint8_t menu, uint8_t btn) {
  for (uint8_t i=0; i<6; i++) {
    buttons[menu][i] = false;
  }
  buttons[menu][btn] = true;
  clearLEDRow(row);
  setLED(row,col,true);
}

//Low-level function to turn an individual LED on or off
void setLED(uint8_t row, uint8_t col, bool onoff) {
  bitWrite(rows[row],col,onoff);
  sendData(MAXOP_DIGIT0+row,rows[row]);
}

//Low-level function to clear all LEDs
void clearLEDs() {
  for (uint8_t row=0; row<=7; row++) {
    clearLEDRow(row);
  }
}

//Low-level function to clear a row
void clearLEDRow(uint8_t row) {
  rows[row] = 0;
  sendData(MAXOP_DIGIT0+row, 0);
}

//Low-level send data function
void sendData(uint16_t cmd, uint8_t data) {
  uint16_t x = (cmd << 8) | data;
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  digitalWrite(MAXPIN_LOAD, LOW);
  SPI.transfer16(x);
  digitalWrite(MAXPIN_LOAD, HIGH);
  SPI.endTransaction();
}
