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

uint8_t rows[8] = {0,0,0,0,0,0,0,0};
uint8_t panelvalue[6] = {0,0,0,0,0,0};

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

  Serial.begin(9600);

  Serial.println("Starting");

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

    /*
    delay(500);
    readAndDisplay();
    */
    delayAndScan();

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

void delayAndScan() {
  for (int i=0; i<10; i++) {
    readAndDisplay();
    delay(50);
  }
}

void readAndDisplay() {
  uint8_t p[6] = {0,0,0,0,0,0};
  p[0] = analogRead(A9)/171; //Range between 0 and 6 (six buttons on pannel 1, 0 means no button pressed)
  p[1] = analogRead(A8)/205; //Range between 0 and 5 (five buttons on panel 2)
  p[2] = analogRead(A3)/171; //Range between 0 and 6 (six buttons on panel 3)
  p[3] = analogRead(A6)/114; //Range between 0 and 9 (nine buttons on panel 4)
  p[4] = analogRead(A7)/171; //Range between 0 and 6 (six buttons on panel 5)
  p[5] = analogRead(A2)/114; //Range between 0 and 9 (nine buttons on panel 6)
  for (int i=0; i<6 i++) {
    if (panelvalue[i]!=p[i]) {
      if (panelvalue[i]==0) {
        buttonPressed(0,p[i]) //Button down
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
  Serial.print("Panel: ");
  Serial.print(panel);
  Serial.print(" Button: ");
  Serial.println(button);
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
