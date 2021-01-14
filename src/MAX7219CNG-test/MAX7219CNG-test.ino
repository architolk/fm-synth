//We always have to include the library
#include "SPI.h"

/*
 Standard Arduino SPI pins:
 - pin 11 is connected to the DataIn 
 - pin 13 is connected to the CLK 
 - pin 10 is connected to LOAD 
 We have only a single MAX72XX.
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

int button = 0;
uint16_t aread = 0;

bool buttons[9] = {false, false, false, false, false, false, false, false, false};

bool startup = true;

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
  /*
  setLed(1,6,true);
  setLed(1,5,true);
  setLed(1,4,true);
  setLed(1,3,true);
  */
  delay(3000);

  clearDisplay();

  //Serial.begin(9600);
}

void loop() {
  for (uint8_t i=4; i<=6; i++) {
    if (startup) {
      setLed(0,i,true);
      //setLed(1,i,true);
    }
    checkAndDelay();
    //delay(500);
    if (startup) {
      setLed(0,i,false);
      //setLed(1,i,false);
    }
    //Serial.println(analogRead(A0));
    //Serial.println(buttonPressed());
  }
}

void checkAndDelay() {
  for (int i = 0; i<50; i++) {
    delay(10);
    int b = buttonPressed();
    if (b!=button) {
      button=b;
      if (button!=0 && button!=5) {
        //Serial.print(aread);
        //Serial.print(" >> ");
        //Serial.println(button);
        if (startup) {
          startup = false;
          clearDisplay();
        }
      }
      if (button==7) {
        startup = true;
      }
      if (button==1) {
        buttons[0] = not(buttons[0]);
        setLed(0,2,buttons[0]);
      }
      if (button==2) {
        buttons[1] = not(buttons[1]);
        setLed(0,0,buttons[1]);
      }
      if (button==3) {
        buttons[2] = not(buttons[2]);
        setLed(0,4,buttons[2]);
      }
      if (button==4) {
        buttons[3] = not(buttons[3]);
        setLed(0,5,buttons[3]);
      }
      if (button==5) {
        buttons[4] = not(buttons[4]);
        setLed(0,6,buttons[4]);
      }
      if (button==6) {
        buttons[5] = not(buttons[5]);
        setLed(0,1,buttons[5]);
      }
    }
  }
}

int buttonPressed() {
  uint16_t b = analogRead(A0);
  aread = b;
  /*
  if (b>90 && b<150) return 1;
  if (b>200 && b<250) return 2;
  if (b>280 && b<380) return 3;
  if (b>400 && b<500) return 4;
  if (b>510 && b<620) return 5;
  if (b>630 && b<710) return 6;
  if (b>750 && b<850) return 7;
  if (b>870 && b<960) return 8;
  if (b>980) return 9;
  */
  if (b>90 && b<250) return 1;
  if (b>300 && b<400) return 2;
  if (b>450 && b<600) return 3;
  if (b>650 && b<750) return 4;
  if (b>800 && b<900) return 5;
  if (b>950) return 6;
  return 0;
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
