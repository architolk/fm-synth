/*
*  dXFM2 synthesizer main module
*
*  this is the main module for the dXFM2 synthesizer
*  the individual IC's are controled from submodules
*  this module will set the pinout and start of the SPI and I2C libraries
*
*/
#include "SPI.h"

void setup() {
  pinMode(MAXPIN_LOAD, OUTPUT); //MAXPIN_LOAD is defined in the submodule
  SPI.begin();
  setupLEDButtons(); //setup instructions for the LED buttons

  splashLEDs(); //default splash screen for the LEDs

  delay(2000); //two seconds splash screen

  clearLEDs(); //LEDs should all be off after splash screen

  //Debugging, not for production
  Serial.begin(9600);
  Serial.println("Starting");
}

void loop() {
  scanLEDButtons();
  delay(50); //Some delay to mitigate bouncing, should be done with timer and not a delay - whatever for now!
}

void doLEDButtonPressed(uint8_t row, uint8_t col, uint8_t menu, uint8_t btn) {
  //Debugging, not for production
  Serial.print("Panel: ");
  Serial.print(panel);
  Serial.print(" Button: ");
  Serial.print(button);
  Serial.print(" Menu: ");
  Serial.print(menu);
  Serial.print(" Btn: ");
  Serial.println(btn);

  if (menu<6) {
    //Operators, so simple toggle (more than one LED can be active)
    toggleLED(row,col,menu,btn);
  } else {
    //Menu mode, so only one LED can be active
    //Need some work: menu 8 & 9 can have only one active LED!
    toggleLEDRow(row,col,menu,btn);
  }
}
