//We always have to include the library
#include "SPI.h"

/*
 Standard Arduino SPI pins:
 - pin 11 is connected to the DataIn
 - pin 13 is connected to the CLK
 - pin 10 is connected to LOAD

 - A2 (pin 16): Analog input
 - A3 (pin 17): Analog input
 - A6 (pin 20): Analog input
 - A7 (pin 21): Analog input
 - A8 (pin 22): Analog input
 - A9 (pin 23): Analog input
 */

const uint8_t MAXPIN_LOAD = 10;
const uint16_t MAXOP_DIGIT0 = 1;
const uint16_t MAXOP_DECODEMODE = 9;
const uint16_t MAXOP_INTENSITY = 10;
const uint16_t MAXOP_SCANLIMIT = 11;
const uint16_t MAXOP_SHUTDOWN = 12;
const uint8_t MAXVAL_OPERATIONAL = 1;
const uint8_t MAXVAL_NONE = 0;

//Mapping van LED-buttons
const uint8_t BTNMAP[8][6] = {{2,0,4,5,6,1},{2,0,1,6,5,4},{0,2,4,1,6,5},{6,1,4,2,0,5},{4,0,5,2,1,6},{2,0,4,6,1,5},{6,1,4,2,0,5},{2,0,4,6,1,5}};

typedef struct {
  uint8_t segment;
  uint8_t digit;
  uint8_t menu;
  uint8_t btn;
} map_type;
const map_type BTNMAP2[6][9] = {{{0,2,7,5},{0,0,7,4},{0,4,7,3},{0,5,7,2},{0,6,7,1},{0,1,7,0},{7,5,9,5},{7,5,9,5},{7,5,9,5}} // {7,5,9,5} means: no led
                               ,{{1,2,5,0},{1,0,5,1},{1,1,5,2},{1,6,5,3},{1,5,5,4},{7,5,9,5},{7,5,9,5},{7,5,9,5},{7,5,9,5}}
                               ,{{2,0,6,5},{2,2,6,4},{2,4,6,3},{2,1,6,2},{2,6,6,1},{2,5,6,0},{7,5,9,5},{7,5,9,5},{7,5,9,5}}
                               ,{{6,0,0,1},{6,2,0,2},{6,4,0,3},{6,1,0,4},{6,6,0,5},{3,6,1,5},{3,1,1,4},{3,4,1,3},{3,2,1,2}}
                               ,{{4,6,4,5},{4,2,3,4},{4,1,3,5},{4,5,2,5},{4,0,2,4},{4,4,2,3},{7,5,9,5},{7,5,9,5},{7,5,9,5}}
                               ,{{5,2,8,0},{5,0,8,1},{5,4,8,2},{5,6,8,3},{5,1,8,4},{7,6,9,3},{7,4,9,2},{7,0,9,1},{7,2,9,0}}
                               };

uint8_t rows[8] = {0,0,0,0,0,0,0,0};
uint8_t panelvalue[6] = {0,0,0,0,0,0};

bool buttons[10][6]; //Current values of the buttons

void setup() {
  pinMode(MAXPIN_LOAD, OUTPUT);
  SPI.begin();
  sendData(MAXOP_SHUTDOWN, MAXVAL_OPERATIONAL);
  sendData(MAXOP_DECODEMODE, MAXVAL_NONE);
  sendData(MAXOP_SCANLIMIT, 7); // 1 = Displays 0 and 1 are active
  sendData(MAXOP_INTENSITY, 10);

  setupButtons();

  clearDisplay();

  setLed(0,2,true);

  setLed(5,2,true);

  setLed(3,2,true);
  setLed(6,2,true);

  setLed(2,2,true);

  setLed(1,2,true);
  setLed(4,2,true);

  delay(2000);

  clearDisplay();

  Serial.begin(9600);

  Serial.println("Starting");

}

void setupButtons() {
  for (uint8_t menu=0; menu<10; menu++) {
    for (uint8_t btn=0; btn<6; btn++) {
      buttons[menu][btn] = false;
    }
  }
}

void loop() {
  for (uint8_t i=0; i<=5; i++) {
    /*
    setLed(0,BTNMAP[0][i],true); //Panel 1 (blue leds)
    setLed(1,BTNMAP[1][i],true); //Panel 2 (red leds)
    setLed(2,BTNMAP[2][i],true); //Panel 3 (green leds)
    setLed(3,BTNMAP[3][i],true); //Panel 4a (orange leds bottom)
    setLed(4,BTNMAP[4][i],true); //Panel 4b (orange leds middle)
    setLed(5,BTNMAP[5][i],true); //Panel 5 (orange leds top)
    setLed(6,BTNMAP[6][i],true); //Panel 6a (green leds left)
    setLed(7,BTNMAP[7][i],true); //Panel 6b (green leds right)
    */

    /*
    delay(500);
    readAndDisplay();
    */
    delayAndScan();

    /*
    setLed(0,BTNMAP[0][i],false);
    setLed(1,BTNMAP[1][i],false);
    setLed(2,BTNMAP[2][i],false);
    setLed(3,BTNMAP[3][i],false);
    setLed(4,BTNMAP[4][i],false);
    setLed(5,BTNMAP[5][i],false);
    setLed(6,BTNMAP[6][i],false);
    setLed(7,BTNMAP[7][i],false);
    */
  }
}

void delayAndScan() {
  for (int i=0; i<10; i++) {
    readAndDisplay();
    delay(50);
  }
}

void readAndDisplay() {
  uint8_t p[6] = {0,0,0,0,0,0};
  p[0] = (analogRead(A9)+85)/171; //Range between 0 and 6 (six buttons on pannel 1, 0 means no button pressed)
  p[1] = (analogRead(A8)+102)/205; //Range between 0 and 5 (five buttons on panel 2)
  p[2] = (analogRead(A3)+85)/171; //Range between 0 and 6 (six buttons on panel 3)
  p[3] = (analogRead(A6)+57)/114; //Range between 0 and 9 (nine buttons on panel 4)
  p[4] = (analogRead(A7)+85)/171; //Range between 0 and 6 (six buttons on panel 5)
  p[5] = (analogRead(A2)+57)/114; //Range between 0 and 9 (nine buttons on panel 6)
  for (int i=0; i<6; i++) {
    if (panelvalue[i]!=p[i]) {
      if (panelvalue[i]==0) {
        buttonPressed(i,p[i]); //Button down
      }
      panelvalue[i]=p[i];
    }
  }
  /*
  Serial.print("Analog: ");
  Serial.print(p1); Serial.print(" - ");
  Serial.print(p2); Serial.print(" - ");
  Serial.print(p3); Serial.print(" - ");
  Serial.print(p4); Serial.print(" - ");
  Serial.print(p5); Serial.print(" - ");
  Serial.println(p6);
  */
}

void buttonPressed(uint8_t panel, uint8_t button) {
  uint8_t segment = BTNMAP2[panel][button-1].segment;
  uint8_t digit = BTNMAP2[panel][button-1].digit;
  uint8_t menu = BTNMAP2[panel][button-1].menu;
  uint8_t btn = BTNMAP2[panel][button-1].btn;
  Serial.print("Panel: ");
  Serial.print(panel);
  Serial.print(" Button: ");
  Serial.print(button);
  Serial.print(" Menu: ");
  Serial.print(menu);
  Serial.print(" Btn: ");
  Serial.println(btn);

  buttons[menu][btn] = !buttons[menu][btn];
  setLed(segment,digit,buttons[menu][btn]);
}

void setLed(uint8_t row, uint8_t col, bool onoff) {
  bitWrite(rows[row],col,onoff);
  sendData(MAXOP_DIGIT0+row,rows[row]);
}

void sendData(uint16_t cmd, uint8_t data) {
  uint16_t x = (cmd << 8) | data;
  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE0));
  digitalWrite(MAXPIN_LOAD, LOW);
  SPI.transfer16(x);
  digitalWrite(MAXPIN_LOAD, HIGH);
  SPI.endTransaction();
}

void clearDisplay() {
  for (uint8_t row=0; row<=7; row++) {
    rows[row] = 0;
    sendData(MAXOP_DIGIT0+row, 0);
  }
}
