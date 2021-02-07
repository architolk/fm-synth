/*
*  Module for the OLED screens
*
*  this module is about controlling the OLED screens via a TCA9548A
*
*/

//Mapping from logical screens to fysical OLEDs
const uint8_t SCRMAP[7] = {5,7,2,4,0,1,6};

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 //Share reset with Arduino reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupScreens() {
  for (uint8_t screen=0; screen<7; screen++) {
    TCA9548A(SCRMAP[screen]);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      for(;;); // Don't proceed, loop forever
    }
  }
}

void splashScreens() {
  for (uint8_t screen=0; screen<7; screen++) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    if (screen<6) {
      //Show splash for operator
      display.setFont(&Dungeon9pt7b);
      display.setCursor(12,22);
      display.print(F("Operator"));
      display.setFont(&Dungeon12pt7b);
      display.setCursor(12,47);
      display.print(F("#"));
      display.print(screen+1);
    } else {
      //Show splash for dXFM2
      display.setFont(&Dungeon12pt7b);
      display.setCursor(20,38);
      display.print(F("dXFM2"));
    }
    //showScreenBorder();
    TCA9548A(SCRMAP[screen]);
    display.display();
  }
}

void initScreens() {
  //Nothing to do: initialization of screens is nothing at the moment
}

//Shows the value of some parameter (fixed to "Volume" at this moment)
void showValueOnScreen(uint8_t screen, uint8_t value) {
  display.clearDisplay();
  display.setFont(&Dungeon12pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,20);
  display.print(F("Volume:"));
  drawPercentbar( 0, 30, 128, 30,value);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void drawPercentbar(int x,int y, int width,int height, uint8_t progress) {
  float bar = ((float)(width-4) / 255) * progress;

  display.drawRect(x, y, width, height, WHITE);
  // Display progress text
  display.setCursor((width/2) -16, y+21 );
  display.setTextColor(WHITE);
  display.print(progress);
  // Bar, inverse: switch colors at text position
  display.fillRect(x+2, y+2, bar , height-4, SSD1306_INVERSE);
}

//Shows a rectangle at the screen's border
void showScreenBorder() {
  display.drawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SSD1306_WHITE);
}

//Low-level function for TCA9548A multiplex switch
void TCA9548A(uint8_t bus) {
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}
