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

//const byte MCP23017 = 0x20; //I2C address of the IC: A0, A1 and A2 are to GND
const byte MCP23017 = 0x24; //I2C address of the IC: A0, A1 to GND, A2 to VCC
const byte GPPUA = 0x0C; //Pull-up resistor PortA;
const byte GPIOA = 0x12;
const byte GPIOB= 0x13;
const byte IOCON = 0x0A;

byte registerA = 0;
byte registerB = 0;

int n = LOW;
int encoderPos = 0;
int encoderPinALast = HIGH;

void setup() {
  Wire.begin();

  Wire.beginTransmission(MCP23017);
  Wire.send(IOCON);
  Wire.send(B00000000); //Enable sequential addresses, 16-bit mode
  Wire.send(B00000000); //Enable sequential addresses, 16-bit mode
  Wire.endTransmission();

  //Default mode of the MCP23017 is GPIO pins as input, so we don't need to set this up

  Wire.beginTransmission(MCP23017);
  Wire.send(GPPUA);
  Wire.send(B00000111); //No pull-ups for Port-A
  Wire.send(B00000111); //Pull-ups for Port-B GPB0 (=pin 1), GPB1 (=pin 2), GPB2 (=pin 3)
  Wire.endTransmission();

  //Simple case: no interupts

  //Start serial communication
  Serial.begin(9600);
  Serial.println("Starting");
}

void loop() {
  readRegisters();
  n = bitRead(registerA,1);
  if ((encoderPinALast == LOW) && (n == HIGH)) {
    if (bitRead(registerA,0) == LOW) {
      encoderPos--;
    } else {
      encoderPos++;
    }
    Serial.println(encoderPos);
  }
  encoderPinALast = n;
  if (bitRead(registerA,2) == LOW) {
    encoderPos = 5;
    Serial.println(encoderPos);
  }
  /*
  Serial.print("Port A: ");
  Serial.print(registerA);
  Serial.print(" Port B: ");
  Serial.println(registerB);
  delay(500);
  */
}

void readRegisters() {
  Wire.beginTransmission(MCP23017);
  Wire.send(GPIOA);
  Wire.endTransmission();
  Wire.requestFrom(MCP23017,2);
  byte aantal = Wire.available();
  if (aantal==2) {
    registerA = Wire.read();
    registerB = Wire.read();
  }
}
