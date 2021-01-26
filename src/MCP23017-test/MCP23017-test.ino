/* Simple test of a MCP23017 chip
*
* Pin layout:
* Pin 1 => To rotary encoder A
* Pin 2 => To rotary encoder B
* Pin 3 => To button
* Pin 9 => To 3.3V
* Pin 10 => To GND
* Pin 12 => To SCL, pin 19 of the Teensy, using 4.7K pull up resistor to 3.3V
* Pin 13 => To SDA, pin 18 of the Teensy, using 4.7K pull up resistor to 3.3V
* Pin 15 => To GND
* Pin 16 => To GND
* Pin 17 => To GND
* Pin 18 => To 3.3 via a 10K pull up resistor
*/

#include <Wire.h>

const byte MCP23017 = 0x20; //I2C address of the IC: A0, A1 and A2 are to GND
const byte GPPUA = 0x0C; //Pull-up resistor PortA;
const byte GPIOA = 0x12;
const byte IOCON = 0x0A;

void setup() {
  Wire.begin();

  Wire.beginTransmission(MCP23017);
  Wire.send(IOCON);
  Wire.send(B01000000); //Enable sequential addresses, 16-bit mode
  Wire.endTransmission();

  //Default mode of the MCP23017 is GPIO pins as input, so we don't need to set this up

  Wire.beginTransmission(MCP23017);
  Wire.send(GPPUA);
  Wire.send(B00000000); //No pull-ups for Port-A
  Wire.send(B00000111); //Pull-ups for Port-B GPB0 (=pin 1), GPB1 (=pin 2), GPB2 (=pin 3)
  Wire.endTransmission();

  //Simple case: no interupts

  //Start serial communication
  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(MCP23017,GPIOA);
  if (Wire.available()==2) {
    Serial.print("Port A: ");
    Serial.print(Wire.receive());
    Serial.print(" Port B: ");
    Serial.println(Wire.receive());
  } else {
    Serial.println("HUH?");
  }
  delay(500);
}
