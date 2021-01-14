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

uint8_t rows[8] = {0,0,0,0,0,0,0,0};

void setup() {
  pinMode(MAXPIN_LOAD, OUTPUT);
  SPI.begin();
  sendData(MAXOP_SHUTDOWN, MAXVAL_OPERATIONAL);
  sendData(MAXOP_DECODEMODE, MAXVAL_NONE);
  sendData(MAXOP_SCANLIMIT, 1); // 1 = Displays 0 and 1 are active
  sendData(MAXOP_INTENSITY, 8);

  clearDisplay();

  setLed(0,6,true);
  setLed(0,5,true);
  setLed(0,4,true);
  setLed(0,2,true);
  setLed(0,1,true);
  setLed(0,0,true);
  delay(3000);

  clearDisplay();

}

void loop() {
  for (uint8_t i=4; i<=6; i++) {
    setLed(0,i,true);
    delay(500);
    setLed(0,i,false);
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
