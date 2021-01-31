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
* Pin 20 => To pin 2 of the Teensy (interupt pin)
*/

#include <Wire.h>

const byte MCP23017 = 0x20; //I2C address of the IC: A0, A1 and A2 are to GND
const byte GPPUA = 0x0C; //Pull-up resistor PortA;
const byte GPIOA = 0x12; //GPIO register PortA
const byte INTCAPA = 0x10; //GPIO values at time of the interupt PortA
const byte IOCON = 0x0A; //Configuration
const byte GPINTENA = 0x04; //Interupt settings PortA

byte registerA = 0;
byte registerB = 0;

int n = LOW;
int encoderPos = 0;
int encoderPinALast = HIGH;

void setup() {
  Wire.begin();

  Wire.beginTransmission(MCP23017);
  Wire.send(IOCON);
  Wire.send(0b01000000); //Enable sequential addresses, 16-bit mode, mirror interupts, active-low interupt
  Wire.send(0b01000000); //Enable sequential addresses, 16-bit mode, mirror interupts, active-low interupt
  Wire.endTransmission();

  //Default mode of the MCP23017 is GPIO pins as input, so we don't need to set this up

  Wire.beginTransmission(MCP23017);
  Wire.send(GPPUA);
  Wire.send(0b00000000); //No pull-ups for Port-A
  Wire.send(0b00000111); //Pull-ups for Port-B GPB0 (=pin 1), GPB1 (=pin 2), GPB2 (=pin 3)
  Wire.endTransmission();

  //Configure interupts
  Wire.beginTransmission(MCP23017);
  Wire.send(GPINTENA);
  Wire.send(0b00000000); //No interupts for Port-A
  Wire.send(0b00000111); //Interupts for Port-B GPB0, GPB1 and GPB2
  Wire.endTransmission();
  //INTCOND and DEFVAL remain at default positions, meaning pins are compared to previous pin value

  //Extra read registers, to reset interrupts
  readRegisters();

  //attach interupt
  attachInterrupt(2, doInterrupt, CHANGE);

  //Start serial communication
  Serial.begin(9600);
  Serial.println("Starting");
}

void loop() {
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
  Wire.send(INTCAPA); //Read registers at time of the interupt
  Wire.endTransmission();
  Wire.requestFrom(MCP23017,2);
  byte aantal = Wire.available();
  if (aantal==2) {
    registerA = Wire.read();
    registerB = Wire.read();
  }
}

void doInterrupt() {
  readRegisters();
  n = bitRead(registerB,2);
  if ((encoderPinALast == LOW) && (n == HIGH)) {
    if (bitRead(registerB,1) == LOW) {
      encoderPos--;
    } else {
      encoderPos++;
    }
    Serial.println(encoderPos);
  }
  encoderPinALast = n;
  if (bitRead(registerB,0) == LOW) {
    encoderPos = 5;
    Serial.println(encoderPos);
  }
}
