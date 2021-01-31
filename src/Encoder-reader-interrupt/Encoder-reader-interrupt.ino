/*
* Test of all encoders
*
* Pin layout:
* - Pin 1 (closed to pins from encoder) INT chip A -> To pin 2 of Teensy
* - Pin 2 INT chip B -> To pin 3 of Teensy
* - Pin 3 3.3V -> To 3V pin of Teensy
* - Pin 4 GND -> To GND pin of Teensy
* - Pin 5 SCL -> To pin 19 of Teensy, using 4.7K pull-up resistor
* - Pin 6 SDA -> To pin 18 of Teensy, using 4.7K pull-up resistor
*/

#include <Wire.h>

const byte MCP23017 = 0x20; //I2C address of the IC: A0, A1 and A2 are to GND
const byte GPPUA = 0x0C; //Pull-up resistor PortA
const byte GPIOA = 0x12; //GPIO register PortA
const byte INTCAPA = 0x10; //GPIO values at time of the interupt PortA
const byte IOCON = 0x0A; //Configuration
const byte GPINTENA = 0x04; //Interupt settings PortA
const byte INTFA = 0x0E; //Interrupt flag register PortA

const uint8_t MCP23017[2] = {0x20,0x24};

int8_t encoder = -1; //Encoder that is used, range 0-9, -1 means: no encoder used
typedef struct {
  bool buttonPressed; //true when button is pressed, remains true while button is pressed
  bool buttonClick; //true when button is clicked, only true ones every button press (resets after button release)
  uint8_t value;
} encoder_type;
encoder_type encoders[10]; //Encoder values 0-9

// 0 = PortA of IC 0x20
// 1 = PortA of IC 0x24
// 2 = PortB of IC 0x20
// 3 = PortB of IC 0x24
uint8_t portsValue[4] = {0,0,0,0};
uint8_t portsValueOld[4] = {0,0,0,0};

typedef struct {
  uint8_t encPort;
  uint8_t encAbit;
  uint8_t encBbit;
  uint8_t btnPort;
  uint8_t btnBit;
} encoderBits_type;                      //0           1           2           3           4           5           6           7           8           9
const encoderBits_type encoderBits[10] = {{1,5,7,1,6},{2,5,6,2,7},{2,4,5,0,3},{0,5,6,0,7},{1,1,2,1,0},{2,1,2,2,0},{0,0,1,0,2},{3,6,7,3,5},{3,3,4,3,2},{3,0,1,1,3}}

bool encoderALastValue[10];

typedef struct {
  uint8_t port;
  uint8_t mask;
  uint8_t encoder;
} encoderMask_type;
const encoderMask_type encodermask[12] = {{3,B11100000,7},{3,B00011100,8},{3,B00000011,9},
                                          {1,B11100000,0},{1,B00001000,9},{1,B00000111,4},
                                          {2,B11100000,1},{2,B00011000,2},{2,B00000111,5},
                                          {0,B11100000,3},{0,B00001000,2},{0,B00000111,6}};

void setupEncoders() {
  for (int i=0; i<10; i++) {
    encoders[i].buttonPressed = FALSE;
    encoders[i].buttonClick = FALSE;
    encoders[i].value = 0;
    encoderALastValue[i] = LOW;
  }
}

void setupMCP23017(uint8_t portOffset) {
  Wire.beginTransmission(MCP23017[portOffset]);
  Wire.send(IOCON);
  Wire.send(B01100000); //Enable sequential addresses, 16-bit mode, mirror interupts, active-low interupt
  Wire.endTransmission();

  //Default mode of the MCP23017 is GPIO pins as input, so we don't need to set this up

  //Configure pull-ups
  Wire.beginTransmission(MCP23017[portOffset]);
  Wire.send(GPPUA);
  Wire.send(B11111111); //Pull-ups for Port-A
  Wire.send(B11111111); //Pull-ups for Port-B
  Wire.endTransmission();

  //Configure interupts
  Wire.beginTransmission(MCP23017[portOffset]);
  Wire.send(GPINTENA);
  Wire.send(B11111111); //Interrupts for Port-A
  Wire.send(B11111111); //Interrupts for Port-B
  Wire.endTransmission();
  //INTCOND and DEFVAL remain at default positions, meaning pins are compared to previous pin value
}

void reactToEncoder() {
  //This function is called whenever an encoder is used
  //It should look at the value of encoders[encoder]
  if (encoder>=0) {
    Serial.print("Encoder: ");
    Serial.print(encoder);
    Serial.print(" buttonPressed: ");
    Serial.print(encoders[encoder].buttonPressed);
    Serial.print(" buttonClick: ");
    Serial.print(encoders[encoder].buttonClick);
    Serial.print(" value: ");
    Serial.println(encoders[encoder].value);
  }
}

void doInterruptA() {
  scanEncoders(0);
}

void doInterruptA() {
  scanEncoders(1);
}

//Only one MCP23017 needs to be scanned at one time, due to separate interrupts
void scanEncoders(uint8_t portOffset) {
  bool somethingHappened = FALSE;
  //Read which input has triggered the interrupt
  readRegister(INTFA,portOffset);
  //Find out which encoder has been turned
  encoder = -1;
  for (int i=0; i<12; i++) {
    if ((encoderMask[i].port==portOffset) || (encoderMask[i].port==(portOffset+2))) {
      if (portsValue[encodermask[i].port] & encodermask[i].mask)!=0) {
        encoder = encodermask[i].encoder;
      }
    }
  }
  //Read the actual values at time of interrupt (will reset the interrupt)
  readRegister(INTCAPA,portOffset);
  //Only check when encoder is not -1. If this happens, we have a problem: interrupt but no encoder found???
  if (encoder>=0) {
    bool n = bitRead(portsValue[encoderBits[encoder].encPort],encoderBits[encoder].encAbit);
    if ((encoderALastValue[encoder] == LOW) && (n == HIGH)) {
      if (bitRead(portsValue[encoderBits[encoder].encPort],encoderBits[encoder].encBbit) == LOW) {
        encoders[encoder].value--;
      } else {
        encoders[encoder].value++;
      }
      somethingHappened = TRUE;
    }
    encoderALastValue[encoder] = n;
    if (bitRead(portsValue[encoderBits[encoder].btnPort],encoderBits[encoder].btnBit) == LOW) {
      if (encoders[encoder].buttonPressed) {
        //Button is still pressed, maybe a turn of the encoder without releasing the button? Not a click!
        encoders[encoder].buttonClick = FALSE;
      } else {
        encoders[encoder].buttonClick = TRUE;
        encoders[encoder].buttonPressed = TRUE;
        somethingHappened = TRUE;
      }
    } else {
      //Button is released, maybe a turn of the encoder? Not a click!
      encoders[encoder].buttonClick = FALSE;
    }
  }
  if (somethingHappened) {
    reactToEncoder();
  }
}

void readRegister(uint8_t reg, uint8_t portOffset) {
  Wire.beginTransmission(MCP23017[portOffset]);
  Wire.send(reg);
  Wire.endTransmission();
  Wire.requestFrom(MCP23017[portOffset],2);
  byte aantal = Wire.available();
  if (aantal==2) {
    portsValue[portOffset + 0] = Wire.read();
    portsValue[portOffset + 2] = Wire.read();
  }
}

void setup() {
  setupEncoders();

  Wire.begin();

  setupMCP23017(0);
  setupMCP23017(1);

  //attach interrupts
  attachInterrupt(2, doInterruptA, CHANGE);
  attachInterrupt(3, doInterruptB, CHANGE);

  Serial.begin(9600);
}

void loop() {
  //Nothing happening, everything is handled by interrupts
}
