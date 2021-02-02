/*
* Test of all encoders
*
* NB: Chip will NOT be reset when new code is uploaded, so please: disconnect before re-upload code!!!
*
* Pin layout:
* - Pin 1 (closed to pins from encoder) INT chip A -> To pin 2 of Teensy
* - Pin 2 INT chip B -> To pin 3 of Teensy
* - Pin 3 3.3V -> To 3V pin of Teensy
* - Pin 4 GND -> To GND pin of Teensy
* - Pin 5 SCL -> To pin 19 of Teensy, using 4.7K pull-up resistor
* - Pin 6 SDA -> To pin 18 of Teensy, using 4.7K pull-up resistor
*
* Important structure is encoder, this is the last used encoder
* and encoders[encoder], which gives you the values of the last used encoder:
* - buttonPressed: true as long as a button is pressed (hold down)
* - buttonClick: true when a button is pressed (but released immediatly thereafter)
* - value: the current value of the encoder, range 0 - 255 (as used by the XFM2)
*
* TODO: speedup the increments of the encoder, depending on the "speed" of the turn
*/

//#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/Dungeon9pt7b.h>
#include <Fonts/Dungeon12pt7b.h>

const uint8_t GPPUA = 0x0C; //Pull-up resistor PortA
const uint8_t GPIOA = 0x12; //GPIO register PortA
const uint8_t INTCAPA = 0x10; //GPIO values at time of the interupt PortA
const uint8_t IOCON = 0x0A; //Configuration
const uint8_t GPINTENA = 0x04; //Interupt settings PortA
const uint8_t INTFA = 0x0E; //Interrupt flag register PortA

const uint8_t MCP23017[2] = {0x20,0x24};

int8_t encoder = -1; //Encoder that is used, range 0-9, -1 means: no encoder used
typedef struct {
  bool buttonPressed; //true when button is pressed, remains true while button is pressed
  bool buttonClick; //true when button is clicked, only true ones every button press (resets after button release)
  uint8_t value;
} encoder_type;
encoder_type encoders[10]; //Encoder values 0-9

bool rotating = false; //debounce management

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
const encoderBits_type encoderBits[10] = {{1,1,0,1,2},{2,5,6,2,7},{2,4,3,0,4},{0,0,2,0,1},{1,5,6,1,7},{2,2,1,2,0},{0,6,7,0,5},{3,7,6,3,5},{3,3,4,3,2},{3,0,1,1,4}};

bool encoderALastValue[10];

typedef struct {
  uint8_t port;
  uint8_t mask;
  uint8_t encoder;
} encoderMask_type;
const encoderMask_type encoderMask[12] = {{3,B11100000,7},{3,B00011100,8},{3,B00000011,9},
                                          {1,B00000111,0},{1,B00010000,9},{1,B11100000,4},
                                          {2,B11100000,1},{2,B00011000,2},{2,B00000111,5},
                                          {0,B00000111,3},{0,B00010000,2},{0,B11100000,6}};

void setupEncoders() {
  for (int i=0; i<10; i++) {
    encoders[i].buttonPressed = false;
    encoders[i].buttonClick = false;
    encoders[i].value = 0;
    encoderALastValue[i] = LOW;
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
  if ( rotating ) delay (1);  // wait a little until the bouncing is done
  scanEncoders(0);
  rotating = false;
}

void doInterruptB() {
  if ( rotating ) delay (1);  // wait a little until the bouncing is done
  scanEncoders(1);
  rotating = false;
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

void showValue(long value) {
  display.clearDisplay();
  display.setFont(&Dungeon12pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,20);
  /*
  display.print(indx++);
  display.print(" - ");
  display.println(value);
  */
  display.print(F("Volume:"));
  drawPercentbar( 0, 30, 128, 30,value);
  display.display();
}

void drawPercentbar(int x,int y, int width,int height, int progress) {
  progress = progress > 100 ? 100 : progress;
  progress = progress < 0 ? 0 :progress;

  float bar = ((float)(width-4) / 100) * progress; 

  display.drawRect(x, y, width, height, WHITE);

  // Display progress text

  display.setCursor((width/2) -16, y+21 );
  display.setTextColor(WHITE);
  display.print(progress);

  // Bar, inverse: switch colors at text position
  display.fillRect(x+2, y+2, bar , height-4, SSD1306_INVERSE);

}

void setup() {
  setupEncoders();

  Wire.begin();

  setupMCP23017(0);
  setupMCP23017(1);

  readRegister(INTCAPA,0);
  readRegister(INTCAPA,1);

  //attach interrupts
  attachInterrupt(2, doInterruptA, CHANGE);
  attachInterrupt(3, doInterruptB, CHANGE);

  Serial.begin(9600);
}

void loop() {
  rotating = true;
  //Nothing happening, everything is handled by interrupts
}
