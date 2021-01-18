//We always have to include the library
#include "SPI.h"

/*
 Standard Arduino SPI pins:
 - pin 11 is connected to the DataIn
 - pin 13 is connected to the CLK
 - pin 10 is connected to LOAD
 */

const uint8_t MAXPIN_LOAD = 10;
const uint16_t MAXOP_DIGIT0 = 1;
const uint16_t MAXOP_DECODEMODE = 9;
const uint16_t MAXOP_INTENSITY = 10;
const uint16_t MAXOP_SCANLIMIT = 11;
const uint16_t MAXOP_SHUTDOWN = 12;
const uint8_t MAXVAL_OPERATIONAL = 1;
const uint8_t MAXVAL_NONE = 0;

const uint8_t BTNMAP[8][6] = {{2,0,4,5,6,1},{2,0,4,5,6,1},{0,2,4,1,6,5},{6,1,4,2,0,5},{2,0,4,5,6,1},{2,0,4,6,1,5},{6,1,4,2,0,5},{2,0,4,6,1,5}};

uint8_t rows[8] = {0,0,0,0,0,0,0,0};

void setup() {
  pinMode(MAXPIN_LOAD, OUTPUT);
  SPI.begin();
  sendData(MAXOP_SHUTDOWN, MAXVAL_OPERATIONAL);
  sendData(MAXOP_DECODEMODE, MAXVAL_NONE);
  sendData(MAXOP_SCANLIMIT, 7); // 1 = Displays 0 and 1 are active
  sendData(MAXOP_INTENSITY, 10);

  clearDisplay();

  setLed(0,2,true);

  setLed(5,2,true);

  setLed(3,2,true);
  setLed(6,2,true);

  setLed(2,2,true);

  setLed(1,2,true);
  setLed(4,2,true);

  delay(2000);

  //clearDisplay();

}

void loop() {
  for (uint8_t i=0; i<=5; i++) {
    setLed(0,BTNMAP[0][i],true); //Panel 1 (blue leds)
    setLed(1,BTNMAP[1][i],true); //Panel 2 (red leds)
    setLed(2,BTNMAP[2][i],true); //Panel 3 (green leds)
    setLed(3,BTNMAP[3][i],true); //Panel 4a (orange leds bottom)
    setLed(4,BTNMAP[4][i],true); //Panel 4b (orange leds middle)
    setLed(5,BTNMAP[5][i],true); //Panel 5 (orange leds top)
    setLed(6,BTNMAP[6][i],true); //Panel 6a (green leds left)
    setLed(7,BTNMAP[7][i],true); //Panel 6b (green leds right)
    delay(500);
    setLed(0,BTNMAP[0][i],false);
    setLed(1,BTNMAP[1][i],false);
    setLed(2,BTNMAP[2][i],false);
    setLed(3,BTNMAP[3][i],false);
    setLed(4,BTNMAP[4][i],false);
    setLed(5,BTNMAP[5][i],false);
    setLed(6,BTNMAP[6][i],false);
    setLed(7,BTNMAP[7][i],false);
  }
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
