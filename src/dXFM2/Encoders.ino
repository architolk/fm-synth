/*
*  Module for the Encoders
*
*  this module is about reading the encoders
*  via two MCP23017 chips
*
*/

//MCP23017 register addresses
const uint8_t GPPUA = 0x0C; //Pull-up resistor PortA
const uint8_t GPIOA = 0x12; //GPIO register PortA
const uint8_t INTCAPA = 0x10; //GPIO values at time of the interupt PortA
const uint8_t IOCON = 0x0A; //Configuration
const uint8_t GPINTENA = 0x04; //Interupt settings PortA
const uint8_t INTFA = 0x0E; //Interrupt flag register PortA

//Addresses of our two MCP23017 chips
const uint8_t MCP23017[2] = {0x20,0x24};

// Array to capture the port status of two MCP23017 chips
// 0 = PortA of IC 0x20
// 1 = PortA of IC 0x24
// 2 = PortB of IC 0x20
// 3 = PortB of IC 0x24
uint8_t portsValue[4] = {0,0,0,0};
uint8_t portsValueOld[4] = {0,0,0,0};

// Mapping of MCP23017 port bits to actual encoder
typedef struct {
  uint8_t encPort;
  uint8_t encAbit;
  uint8_t encBbit;
  uint8_t btnPort;
  uint8_t btnBit;
} encoderBits_type;
const encoderBits_type encoderBits[10] = {
  {1,1,0,1,2}  //0
  ,{2,5,6,2,7} //1
  ,{2,4,3,0,4} //2
  ,{0,0,2,0,1} //3
  ,{1,5,6,1,7} //4
  ,{2,2,1,2,0} //5
  ,{0,6,7,0,5} //6
  ,{3,7,6,3,5} //7
  ,{3,3,4,3,2} //8
  ,{3,0,1,1,4} //9
};

// Mapping of MCP23017 port bits to actual encoder - mask: which encoder is used
typedef struct {
  uint8_t port;
  uint8_t mask;
  uint8_t encoder;
} encoderMask_type;
const encoderMask_type encoderMask[12] = {
  {3,0b11100000,7},{3,0b00011100,8},{3,0b00000011,9},
  {1,0b00000111,0},{1,0b00010000,9},{1,0b11100000,4},
  {2,0b11100000,1},{2,0b00011000,2},{2,0b00000111,5},
  {0,0b00000111,3},{0,0b00010000,2},{0,0b11100000,6}
};

int8_t encoder = -1; //Encoder that is used, range 0-9, -1 means: no encoder used
typedef struct {
  bool buttonPressed; //true when button is pressed, remains true while button is pressed
  bool buttonClick; //true when button is clicked, only true ones every button press (resets after button release)
  uint8_t value;
} encoder_type;
encoder_type encoders[10]; //Encoder values 0-9

bool encoderALastValue[10];

void setupEncoders() {
  //Initialize values
  for (int i=0; i<10; i++) {
    encoders[i].buttonPressed = false;
    encoders[i].buttonClick = false;
    encoders[i].value = 0;
    encoderALastValue[i] = LOW;
  }

  //Setup the MCP23017 chips
  setupMCP23017(0);
  setupMCP23017(1);

  //Read interupt registers, this will reset the interupts (keeping them in sync with the Teensy interupts!)
  readRegister(INTCAPA,0);
  readRegister(INTCAPA,1);

  //attach interrupts
  attachInterrupt(2, doInterruptA, CHANGE);
  attachInterrupt(3, doInterruptB, CHANGE);
}

//Interrupt routine for chip A
void doInterruptA() {
  scanEncoder(0);
}

//Interrupt routine for chip B
void doInterruptB() {
  scanEncoder(1);
}

//Only one MCP23017 needs to be scanned at one time, due to separate interrupts
void scanEncoders(uint8_t portOffset) {
  bool somethingHappened = false;
  //Read which input has triggered the interrupt
  readRegister(INTFA,portOffset);
  //Find out which encoder has been turned
  //Don't reset the encoder! Interrupt occur to often, so we need to know which to look at!
  //By not resetting the encoder, we have some memory which encoder is turned!
  //encoder = -1;
  for (int i=0; i<12; i++) {
    if ((encoderMask[i].port==portOffset) || (encoderMask[i].port==(portOffset+2))) {
      if ((portsValue[encoderMask[i].port] & encoderMask[i].mask)!=0) {
        encoder = encoderMask[i].encoder;
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
        if (encoders[encoder].value>0) { //Don't go below zero
          somethingHappened = true;
          encoders[encoder].value--;
        }
      } else {
        if (encoders[encoder].value<255) { //Don't go above 255
          somethingHappened = true;
          encoders[encoder].value++;
        }
      }
    }
    encoderALastValue[encoder] = n;
    if (bitRead(portsValue[encoderBits[encoder].btnPort],encoderBits[encoder].btnBit) == LOW) {
      if (encoders[encoder].buttonPressed) {
        //Button is still pressed, maybe a turn of the encoder without releasing the button? Not a click!
        encoders[encoder].buttonClick = false;
      } else {
        encoders[encoder].buttonClick = true;
        encoders[encoder].buttonPressed = true;
        somethingHappened = true;
      }
    } else {
      //Button is released, maybe a turn of the encoder? Not a click!
      encoders[encoder].buttonPressed = false;
      encoders[encoder].buttonClick = false;
    }
  }
  if (somethingHappened) {
    //Implementated at main level, return the encoder used, and the (new) value of the encoder
    if (encoder>=0) {
      doEncoderUsed(encoder,encoders[encoder].buttonClick,encoders[encoder].value);
    }
  }
}

void setupMCP23017(uint8_t portOffset) {
  Wire.beginTransmission(MCP23017[portOffset]);
  Wire.send(IOCON);
  Wire.send(0b01000000); //Enable sequential addresses, 16-bit mode, mirror interupts, active-low interupt
  Wire.send(0b01000000); //Enable sequential addresses, 16-bit mode, mirror interupts, active-low interupt
  Wire.endTransmission();

  //Default mode of the MCP23017 is GPIO pins as input, so we don't need to set this up

  //Configure pull-ups
  Wire.beginTransmission(MCP23017[portOffset]);
  Wire.send(GPPUA);
  Wire.send(0b11111111); //Pull-ups for Port-A
  Wire.send(0b11111111); //Pull-ups for Port-B
  Wire.endTransmission();

  //Configure interupts
  Wire.beginTransmission(MCP23017[portOffset]);
  Wire.send(GPINTENA);
  Wire.send(0b11111111); //Interrupts for Port-A
  Wire.send(0b11111111); //Interrupts for Port-B
  Wire.endTransmission();
  //INTCOND and DEFVAL remain at default positions, meaning pins are compared to previous pin value
}

//Low-level function that reads a register from the MCP23017
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