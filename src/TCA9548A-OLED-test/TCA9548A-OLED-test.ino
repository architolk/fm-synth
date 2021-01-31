#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//                                              1                   2                   3                   4                   5                   6
//                            1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
const uint8_t WAVE_SINUS[] = {1,3,3,3,3,3,3,3,3,3,2,3,2,2,3,2,2,2,2,6,2,2,6,2,6,6,6,6,6,6,6,6,6,4,6,6,6,6,6,6,6,6,6,2,6,2,2,6,2,2,2,2,3,2,2,3,2,3,3,3,3,3,3,3,3,3,0,0,0};

void setup() {

  // Give the TCA9548A time to boot
  //delay(1000);
  Wire.begin();
  // Set mux
  TCA9548A(2);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    for(;;); // Don't proceed, loop forever
  }
  TCA9548A(1);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    for(;;); // Don't proceed, loop forever
  }
  TCA9548A(4);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    for(;;); // Don't proceed, loop forever
  }
  TCA9548A(5);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    for(;;); // Don't proceed, loop forever
  }
  TCA9548A(6);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    for(;;); // Don't proceed, loop forever
  }
  TCA9548A(7);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    for(;;); // Don't proceed, loop forever
  }
  TCA9548A(0);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    for(;;); // Don't proceed, loop forever
  }

}

void loop() {
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  // Clear the buffer
  display.clearDisplay();
  showRectangle();
  TCA9548A(0);
  display.display();
  
  display.clearDisplay();
  showRectangle();
  showHelloWorld();
  TCA9548A(2);
  display.display();

  display.clearDisplay();
  showRectangle();
  showCurve();
  TCA9548A(1);
  display.display();

  display.clearDisplay();
  showRectangle();
  showCurve();
  TCA9548A(5);
  display.display();

  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Dadada"));
  showRectangle();
  TCA9548A(4);
  display.display();

  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Display 6"));
  showRectangle();
  TCA9548A(6);
  display.display();

  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Display 7"));
  showRectangle();
  TCA9548A(7);
  display.display();

}

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

void showRectangle() {
  display.drawRect(0,0,128,64,SSD1306_WHITE);
}

void showHelloWorld() {
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);
}

void showCurve() {
  uint8_t x = 10;
  uint8_t y = 20;
  for( uint8_t i=0; i<68; i++) {
    display.drawPixel(x, y, SSD1306_WHITE);
    display.drawPixel(x+1, y, SSD1306_WHITE); //A bit fatter
    switch (WAVE_SINUS[i]) {
      case 1: y--; break;
      case 2: x++; break;
      case 3: x++; y--; break;
      case 4: y++; break;
      case 6: x++; y++; break;
    }
  }
}
