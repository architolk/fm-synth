/*
*  Module for the OLED screens
*
*  this module is about controlling the OLED screens via a TCA9548A
*
*/

//Mapping from logical screens to fysical OLEDs
const uint8_t SCRMAP[7] = {5,7,2,4,0,1,6};

//Note names
const String NOTES[12] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};

//Pie chart constants for radius 20
#define PIERADIUS 20
const uint8_t PIEPOS[PIERADIUS] PROGMEM = {4,8,9,11,12,13,14,15,16,17,17,18,18,19,19,19,20,20,20,20};

//Filter graph constants for height 40
#define GRAPHHEIGHT 40
const uint8_t FILTERGRAPH[GRAPHHEIGHT] PROGMEM = {0,3,5,6,7,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17,18,18,19,19,20,20,21,21,22,22,23,24,25,26,28,31};

//Algorithm placement
//0-5 = horizontal placement
//0,8,16,24 = vertical placement
//128 = feedback
//64 = shorten length of vertical line out of box
//32 = create an extra vertical line into the box
const uint8_t ALGOPOS[32][8] PROGMEM = {
  {0b00011100,0b00010100,0b00011101,0b00010101,0b00001101,0b10000101,1,0}, //1
  {0b00011100,0b10010100,0b00011101,0b00010101,0b00001101,0b00000101,1,0}, //2
  {0b00011100,0b00010100,0b00001100,0b00011101,0b00010101,0b10001101,1,0}, //3
  {0b00011100,0b00010100,0b00001100,0b00011101,0b00010101,0b00001101,1,0}, //4
  {0b00011011,0b00010011,0b00011100,0b00010100,0b00011101,0b10010101,2,0}, //5
  {0b00011011,0b00010011,0b00011100,0b00010100,0b00011101,0b00010101,2,0}, //6
  {0b00011011,0b00010011,0b00011100,0b00010100,0b01010101,0b10001101,1,4}, //7
  {0b00011011,0b00010011,0b00011100,0b10010100,0b01010101,0b00001101,1,4}, //8
  {0b00011011,0b10010011,0b00011100,0b00010100,0b01010101,0b00001101,1,4}, //9
  {0b00011011,0b00010011,0b10001011,0b00011100,0b00010100,0b01010101,1,4}, //10
  {0b00011011,0b00010011,0b00001011,0b00011100,0b00010100,0b11010101,1,4}, //11
  {0b00011010,0b10010010,0b00011100,0b01010011,0b00010100,0b01010101,2,3}, //12
  {0b00011010,0b00010010,0b00011100,0b01010011,0b00010100,0b11010101,2,3}, //13
  {0b00011011,0b00010011,0b00011100,0b00010100,0b01001100,0b11001101,1,4}, //14
  {0b00011011,0b10010011,0b00011100,0b00010100,0b00001100,0b01001101,1,4}, //15
  {0b00011100,0b01010011,0b00010100,0b00001100,0b01010101,0b10001101,0,3}, //16
  {0b00011100,0b11010011,0b00010100,0b00001100,0b01010101,0b00001101,0,3}, //17
  {0b00011100,0b01010011,0b10010100,0b01010101,0b00001101,0b00000101,0,3}, //18
  {0b00011011,0b00010011,0b00001011,0b00011100,0b00111101,0b10010100,2,4}, //19
  {0b00111010,0b00011011,0b10010011,0b00011101,0b01010100,0b00010101,3,4}, //20
  {0b00011010,0b00111011,0b10010010,0b00011100,0b00111101,0b00010100,3,4}, //21
  {0b00011010,0b00010010,0b00111011,0b00011100,0b00111101,0b10010100,3,3}, //22
  {0b00011010,0b00011011,0b00010011,0b00011100,0b00111101,0b10010100,3,4}, //23
  {0b00011001,0b00011010,0b00111011,0b00011100,0b00111101,0b10010100,4,3}, //24
  {0b00011001,0b00011010,0b00011011,0b00011100,0b00111101,0b10010100,4,4}, //25
  {0b00011010,0b00011011,0b00010011,0b00011101,0b01010100,0b10010101,3,4}, //26
  {0b00011010,0b00011011,0b10010011,0b00011101,0b01010100,0b00010101,3,4}, //27
  {0b00011011,0b00010011,0b00011100,0b00010100,0b10001100,0b00011101,2,0}, //28
  {0b00011010,0b00011011,0b00011100,0b00010100,0b00011101,0b10010101,3,0}, //29
  {0b00011010,0b00011011,0b00011100,0b00010100,0b10001100,0b10011101,3,0}, //30
  {0b00011001,0b00011010,0b00011011,0b00011100,0b00011101,0b10010101,4,0}, //31
  {0b00011000,0b00011001,0b00011010,0b00011011,0b00011100,0b10011101,5,0}  //32
};

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

void clearScreen(uint8_t screen) {
  display.clearDisplay();

  TCA9548A(SCRMAP[screen]);
  display.display();
}

//Shows an errorcode in the master screen (bottom)
void showError(uint8_t err) {
  display.clearDisplay();
  display.setFont(&Dungeon12pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,30);
  display.print(F("ERROR"));

  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setCursor(0,60);
  switch(err) {
    case ERR_UNIT: display.print(F("Set unit")); break;
    case ERR_DUMP: display.print(F("Dump wrong")); break;
    case ERR_LOAD: display.print(F("Load error")); break;
    case ERR_INIT: display.print(F("Init error")); break;
    default: display.print(F("Unknown"));
  }

  TCA9548A(SCRMAP[6]);
  display.display();
}

//Debug printing
void showDebug(uint16_t debug) {
  display.clearDisplay();
  display.setFont(&Dungeon12pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,30);
  display.print(F("DEBUG"));

  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setCursor(0,60);
  display.print(debug);

  TCA9548A(SCRMAP[6]);
  display.display();
  delay(2000); //Make sure the debug message is visible for two seconds
}

void showMessage(const String& msg) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,32);
  display.print(msg);

  TCA9548A(SCRMAP[6]);
  display.display();
}

void showPatchMenu(uint8_t patch) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,20);
  display.print(F("Active: "));
  display.print(patchSelect);

  display.setCursor(0,50);
  display.print(F("Patch: "));
  display.setFont(&Dungeon12pt7b);
  display.print(patch);

  TCA9548A(SCRMAP[6]);
  display.display();
}

//Shows a note on the screen, with respect to a certain offset
void showNoteOnScreen(uint8_t screen, uint8_t value, uint8_t offset, bool relative, uint8_t lscale, uint8_t lcurve, uint8_t rscale, uint8_t rcurve) {
  display.clearDisplay();

  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  if (relative) {
    display.setCursor(5,14);
    display.print(F("Transpose"));
  }
  uint16_t pos = value;
  pos = (pos*63/offset)+1;
  if (relative) {
    display.drawLine(0,32,127,32,SSD1306_WHITE);
    display.drawLine(0,33,127,33,SSD1306_WHITE);
  }
  display.drawLine(pos,27,pos,37,SSD1306_WHITE);

  display.setFont(&Dungeon12pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(62-(getStringWidth(NOTES[value%12])+getNumberWidth((value+60-offset)/12))/2,63);
  display.print(NOTES[value%12]);
  display.print((value+48-offset)/12); //C4 = 60, if offset!=60, compensate so offset = C4
  display.setFont(&Dungeon9pt7b);
  if (relative) {
    if (value<offset) {
      display.setCursor(0,63);
      display.print(F("-"));
      display.print(offset-value);
    }
    if (value>offset) {
      display.setCursor(100,63);
      display.print(value-offset);
    }
  } else {
    if (lcurve<2) {
      display.setCursor(0,63);
    } else {
      display.setCursor(0,14);
    }
    display.print(lscale);
    if (rcurve<2) {
      drawNumber(rscale,127,63);
    } else {
      drawNumber(rscale,127,14);
    }
    for (uint8_t i=0; i<128; i++) {
      //Left part
      float y = 32;
      switch (lcurve) {
        case 0: y = y + i*i*0.008*lscale/255; break; //Exponential decrease (y=0 = top, so decrease is y+)
        case 1: y = y + i*0.4*lscale/255; break; //Linear decrease
        case 2: y = y - i*0.4*lscale/255; break; //Linear increase (y=0 = top, so increase is y-)
        case 3: y = y - i*i*0.008*lscale/255; break;; //Exponential increase
      }
      if (i<=pos && y>=0 && y<=63) {
        display.drawPixel(pos-i,y,SSD1306_WHITE);
      }
      //Right part
      y = 32;
      switch (rcurve) {
        case 0: y = y + i*i*0.008*rscale/255; break; //Exponential decrease
        case 1: y = y + i*0.4*rscale/255; break; //Linear decrease
        case 2: y = y - i*0.4*rscale/255; break; //Linear increase
        case 3: y = y - i*i*0.008*rscale/255; break;; //Exponential increase
      }
      if (i<=127-pos && y>=0 && y<=63) {
        display.drawPixel(pos+i,y,SSD1306_WHITE);
      }
    }
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showMonoPolyOnScreen(uint8_t screen, uint8_t value) {
  display.clearDisplay();

  display.setFont(&Dungeon12pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  if (value==1) {
    display.setCursor(25,40);
    display.print("Mono");
  } else {
    display.setCursor(30,40);
    display.print("Poly");
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showPortaModeOnScreen(uint8_t screen, uint8_t value) {
  display.clearDisplay();

  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  switch (value) {
    case 0: display.setCursor(20,30); display.print(F("Glide off")); break;
    case 1: display.setCursor(30,30); display.print(F("Glide")); break;
    case 2: display.setCursor(25,20); display.print(F("Legato")); display.setCursor(25,40); display.print(F("Glide")); break;
    default: display.print(F("Unknown glide")); break;
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showTuningOnScreen(uint8_t screen, uint8_t value) {
  display.clearDisplay();

  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  if (value==0) {
    display.setCursor(25,30);
    display.print(F("Normal"));
    display.setCursor(25,50);
    display.print(F("tuning"));
  } else {
    display.setCursor(5,40);
    display.print(F("Tuning  #"));
    display.print(value);
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showPanOnScreen(uint8_t screen, uint8_t value) {
  display.clearDisplay();

  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5,14);
  display.print(F("Pan"));

  uint16_t pos = value;
  pos = (pos*63/128)+1;
  display.drawLine(0,30,127,30,SSD1306_WHITE);
  display.drawLine(0,31,127,31,SSD1306_WHITE);
  display.drawLine(pos,25,pos,35,SSD1306_WHITE);

  display.setFont(&Dungeon12pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(58,60);
  if (value==128) {
    display.print(F("C"));
  } else {
    if (value<128) {
      if (value==0) {
        display.print(F("L"));
      } else {
        display.setFont(&Dungeon9pt7b);
        display.setCursor(58-getNumberWidth(128-value)/2,60);
        display.print(F("L"));
        display.print(128-value);
      }
    } else {
      if (value==255) {
        display.print(F("R"));
      } else {
        display.setFont(&Dungeon9pt7b);
        display.setCursor(58-getNumberWidth(value-128)/2,60);
        display.print(F("R"));
        display.print(value-128);
      }
    }
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void drawMenuItem(uint8_t nr, const String& param) {
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,12);
  display.print(nr);
  display.print(F(" "));
  display.print(param);
}

void showParamMenuOnScreen(uint8_t nr, const String& param, String value, uint8_t screen) {
  display.clearDisplay();
  drawMenuItem(nr,param);

  display.setCursor(0,40);
  display.print(value);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showParamValueMenuOnScreen(uint8_t nr, const String& prmname, uint16_t offset, uint8_t param, uint8_t value, uint8_t screen) {
  display.clearDisplay();
  drawMenuItem(nr,prmname);

  display.setCursor(0,48);
  display.print(offset+param);

  display.drawRect(60,32,60,20,SSD1306_WHITE);
  drawNumber(value,110,48);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void drawOperatorBox(uint8_t x, uint8_t y, uint8_t l, uint8_t nr, bool feedback, bool input) {
  display.drawRect(x,y,10,10,SSD1306_WHITE);
  display.drawLine(x+5,y+10,x+5,y+10+l,SSD1306_WHITE);
  if (input) {
    display.drawLine(x+5,y-2,x+5,y,SSD1306_WHITE);
  }
  if (feedback) {
    display.drawLine(x+5,y+12,x+12,y+12,SSD1306_WHITE);
    display.drawLine(x+12,y+12,x+12,y-2,SSD1306_WHITE);
    display.drawLine(x+12,y-2,x+5,y-2,SSD1306_WHITE);
    display.drawLine(x+5,y-2,x+5,y,SSD1306_WHITE);
  }
  display.setCursor(x+2,y+1);
  display.print(nr);
}

void showAlgorithmMenuOnScreen(uint8_t nr, const String& param, uint8_t algo, uint8_t screen) {
  display.clearDisplay();
  drawMenuItem(nr,param);

  display.setCursor(8,30);
  display.print(algo+1);

  display.setFont(); //default font
  for (uint8_t op=0; op<6; op++) {
    drawOperatorBox(6+(ALGOPOS[algo][op] & 0b111)*20,6+((ALGOPOS[algo][op] & 0b11000)/8)*14,5-(ALGOPOS[algo][op] & 64)/16,op+1,(ALGOPOS[algo][op] & 128)==128,(ALGOPOS[algo][op] & 32)==32);
  }
  if (ALGOPOS[algo][6]>0) {
    display.drawLine(11+(ALGOPOS[algo][0] & 0b111)*20,63,11+((ALGOPOS[algo][0] & 0b111)+ALGOPOS[algo][6])*20,63,SSD1306_WHITE);
  }
  if (ALGOPOS[algo][7]>0) {
    if (algo==13 || algo==14) {
      display.drawLine(11+(ALGOPOS[algo][7])*20,32,111,32,SSD1306_WHITE);
    } else {
      display.drawLine(11+(ALGOPOS[algo][7])*20,46,111,46,SSD1306_WHITE);
      if (algo==19 || algo==20) {
        display.drawLine(11+(ALGOPOS[algo][7])*20-40,46,111-40,46,SSD1306_WHITE);
      }
    }
  }

  if (algo==3) {
    display.drawLine(111,60,118,60,SSD1306_WHITE);
    display.drawLine(118,60,118,18,SSD1306_WHITE);
    display.drawLine(118,18,111,18,SSD1306_WHITE);
    display.drawLine(111,18,111,20,SSD1306_WHITE);
  }
  if (algo==5) {
    display.drawLine(111,60,118,60,SSD1306_WHITE);
    display.drawLine(118,60,118,32,SSD1306_WHITE);
    display.drawLine(118,32,111,32,SSD1306_WHITE);
    display.drawLine(111,32,111,34,SSD1306_WHITE);
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showMixerOnScreen(uint8_t screen, uint8_t left, uint8_t right, uint8_t unit) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,12);
  display.print(F("Unit "));
  display.print(unit+1);

  display.setCursor(0,36);
  display.print(F("L"));
  drawPercentbar( 20, 20, 108, 20,left);

  display.setCursor(0,60);
  display.print(F("R"));
  drawPercentbar( 20, 44, 108, 20,right);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

//Shows the value of some parameter (fixed to "Volume" at this moment)
void showValueOnScreen(const String& param, uint8_t screen, uint8_t value) {
  display.clearDisplay();
  if (param.length()>7) {
    display.setFont(&Dungeon9pt7b);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,15);
  } else {
    display.setFont(&Dungeon12pt7b);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,20);
  }
  display.print(param);
  drawPercentbar( 0, 30, 128, 30,value);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showVolumeUnitOnScreen(uint8_t screen, uint8_t value, uint8_t unit) {
  display.clearDisplay();

  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,14);
  display.print(F("Volume U"));
  display.print(unit+1);

  drawPercentbar( 0, 30, 128, 30,value);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showVolumeOnScreen(uint8_t screen, uint8_t value) {
  if (displayMode==DISPLAY_OVERVIEW) {
    display.clearDisplay();

    display.setFont(&Dungeon9pt7b);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,14);
    display.print(F("Patch: "));
    display.print(patchSelect);
    if (patchChanged) {
      display.print(F("*"));
    }

    drawPercentbar( 0, 30, 128, 30,value);

    TCA9548A(SCRMAP[screen]);
    display.display();
  } else {
    showValueOnScreen(F("Volume"),screen,value);
  }
}

void showOperatorOverviewOnScreen(uint8_t screen, env_type env, uint8_t level, uint8_t ratio, uint8_t rfine, bool feedbackOn) {
  display.clearDisplay();

  display.setFont(&Dungeon12pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,17);
  display.print(level);
  uint16_t lw = getNumberWidth(level);
  if (feedbackOn) {
    display.fillRect(0, 0, 2+lw , 20, SSD1306_INVERSE);
  }

  uint16_t rw = getNumberWidth(ratio);
  display.setFont(&Dungeon9pt7b);
  rw = rw + getNumberWidth(rfine);
  display.setFont(&Dungeon12pt7b);

  display.setCursor(105-rw,17);
  display.print(F("1:"));
  display.print(ratio);

  display.setFont(&Dungeon9pt7b);
  display.print(F("."));
  display.print(rfine);

  showEnvelope(35,28,env);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showWaveOnScreen(const int8_t wave[122], uint8_t screen) {
  display.clearDisplay();
  for (uint8_t i=1; i<122; i++) {
    display.drawLine(1+i,32+wave[i-1]/4,2+i,32+wave[i]/4,SSD1306_WHITE);
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showFeedbackOnScreen(uint8_t screen, uint8_t value, bool feedbackOn) {
  display.clearDisplay();
  if (feedbackOn) {
    display.setFont(&Dungeon12pt7b);
  } else {
    display.setFont(&Dungeon9pt7b);
  }
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,20);
  if (feedbackOn) {
    display.print(F("Feedback"));
  } else {
    display.print(F("No feedback"));
  }
  drawPercentbar( 0, 30, 128, 30,value);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showLFOSyncOnScreen(uint8_t screen, uint8_t value) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,25);
  if (value<2) {
    display.print(F("Single LFO"));
  } else {
    display.print(F("Multi LFO"));
  }
  display.setCursor(0,55);
  if ((value%2)==0) {
    display.print(F("Free running"));
  } else {
    display.print(F("Key sync"));
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showOutputGainOnScreen(uint8_t screen, uint8_t outputval, uint8_t gainval) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,20);
  display.print(F("Output"));
  drawPercentbar( 0, 30, 128, 30,outputval);

  display.setCursor(100,20);
  display.print(F("+"));
  drawNumber(gainval*6,127,20);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showOSCRatioOnScreen(uint8_t screen, uint8_t ratio, uint8_t mode) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.drawRect(0,10,50,50,SSD1306_WHITE);
  display.setCursor(15,28);
  display.print(F("#1"));
  display.fillRect(2,12,46,20,SSD1306_INVERSE);
  display.drawLine(0,33,49,33,SSD1306_WHITE);

  display.drawRect(70,10,50,50,SSD1306_WHITE);
  display.setCursor(80,28);
  display.print(F("#2"));
  if (mode==1) {
    display.fillRect(72,12,46,20,SSD1306_INVERSE);
  }
  display.drawLine(70,33,119,33,SSD1306_WHITE);

  display.setFont(&Dungeon9pt7b);
  display.setCursor(58,50);
  display.print(F(":"));

  display.setCursor(30,50);
  display.print(F("1"));

  display.setCursor(75,50);
  display.print(ratio);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showRatioOnScreen(uint8_t screen, bool isPitch, uint8_t toggle, uint8_t coarse, uint8_t fine, uint8_t pitch) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  if (isPitch) {
    display.setFont(&Dungeon9pt7b);
    display.setCursor(0,15);
    display.print(F("Pitch"));
    float pitch = fine;
    pitch = 0.34*pitch*pitch/(256*256) + 0.66*pitch/256; //Approximation: actual conversion is 2^(pitch/256)-1 for equal temperament
    pitch = (32.7 * coarse) * (1 + pitch); //Coarse is spot on, fine might be 0-2 Hz off
    drawNumber(pitch,127,15);
    display.setCursor(96,30);
    display.print(F("Hz"));
  } else {
    display.setFont(&Dungeon12pt7b);
    display.setCursor(0,20);
    display.print(F("Ratio"));
  }

  display.setFont(&Dungeon12pt7b);
  display.setCursor(15,50);
  display.print(F("1:"));
  display.print(coarse);
  uint16_t cw = getNumberWidth(coarse);

  display.setFont(&Dungeon9pt7b);
  display.print(F("."));
  display.print(fine);
  uint16_t fw = getNumberWidth(fine);

  float pitchperc = pitch;
  pitchperc = (pitchperc-128)*100/127;
  if (pitch<128 && pitchperc>-1) {
    pitchperc = -1;
  }
  if (pitch>128 && pitchperc<1) {
    pitchperc = 1;
  }
  drawNumber(pitchperc,104,50);
  uint16_t pw = getNumberWidth(pitchperc);
  display.print(F("%"));

  if (toggle==2) {
    display.drawLine(104-pw,60,120,60,SSD1306_WHITE);
    display.drawLine(104-pw,61,120,61,SSD1306_WHITE);
  } else {
    if (toggle==0) {
      display.drawLine(15,60,31+cw,60,SSD1306_WHITE);
      display.drawLine(15,61,31+cw,61,SSD1306_WHITE);
    } else {
      display.drawLine(31+cw,60,36+cw+fw,60,SSD1306_WHITE);
      display.drawLine(31+cw,61,36+cw+fw,61,SSD1306_WHITE);
    }
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showEnvOperatorOnScreen(uint8_t screen, uint8_t op, uint8_t envmode) {
  display.clearDisplay();

  display.setFont(&Dungeon9pt7b);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0,12);
  switch (envmode) {
    case ENVMODE_ADDSRR: display.print("AddSrr XFM2"); break;
    case ENVMODE_ADSR: display.print("ADSR"); break;
    case ENVMODE_ASR: display.print("ASR Plucked"); break;
  }

  display.setTextSize(2);
  display.setCursor(40,50);
  display.print(F("#"));
  display.print(op+1);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showEffectsRoutingOnScreen(uint8_t screen, uint8_t routing, uint8_t bcdepth, uint8_t dedepth) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,20);
  display.print(F("EFX Routing"));

  display.setCursor(15,40);
  if (routing==0) {
    display.print("C>P>A>D");
  } else {
    display.print("D>C>P>A");
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showEffectsStatusOnScreen(uint8_t screen, const String& name1, uint8_t depth1, const String& name2, uint8_t depth2, const String& name3, uint8_t depth3) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,20);
  display.print(name1);
  drawNumber(depth1,127,20);

  display.setCursor(0,40);
  display.print(name2);
  drawNumber(depth2,127,40);

  if (name3.length()>0) {
    display.setCursor(0,60);
    display.print(name3);
    drawNumber(depth3,127,60);
  }

TCA9548A(SCRMAP[screen]);
  display.display();
}

void ShowFilterMessageOnScreen(uint8_t screen, bool lopass, bool hipass) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  if (lopass) {
    display.setCursor(20,20);
    display.print(F("Low pass"));
  }
  if (hipass) {
    display.setCursor(20,20);
    display.print(F("High pass"));
  }

  display.setFont(&Dungeon12pt7b);
  display.setCursor(20,50);
  display.print(F("Filter"));

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showFilterOnScreen(uint8_t screen, uint8_t lopass, uint8_t hipass) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,12);
  display.print(hipass);
  drawNumber(lopass,127,12);

  //TODO: Show filter graph, calculated from hi & lo pass
  drawCurve(lopass/2,hipass/2);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void drawCurve(uint8_t lopass, uint8_t hipass) {
  uint8_t x1 = 0;
  uint8_t x2 = 0;
  for (uint8_t y=1; y<40; y++) {
    x1 = x2;
    x2 = FILTERGRAPH[y];
    if (x2+hipass<31) {
      x2 = 0;
    } else {
      x2 = x2+hipass-31;
    }
    display.drawLine(x1,60-y,x2,59-y,SSD1306_WHITE);
  }
  for (uint8_t y=39; y>0; y--) {
    x1 = x2;
    x2 = lopass+31-FILTERGRAPH[y];
    if (x2>127) {
      x2 = 127;
    }
    display.drawLine(x1,59-y,x2,60-y,SSD1306_WHITE);
  }
  display.drawLine(x2,59,127,59,SSD1306_WHITE);
}

void showDelayModeOnScreen(uint8_t screen, uint8_t mode) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  switch (mode) {
    case 0: display.setCursor(20,20); display.print(F("Stereo")); break;
    case 1: display.setCursor(25,20); display.print(F("Cross")); break;
    case 2: display.setCursor(20,20); display.print(F("Bounce")); break;
  }

  display.setFont(&Dungeon12pt7b);
  display.setCursor(10,50);
  display.print(F("Delay"));

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showAMModeOnScreen(uint8_t screen) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(15,25);
  display.print(F("Amplitude"));
  display.setCursor(15,50);
  display.print(F("Modulation"));

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showReverbModeOnScreen(uint8_t screen, uint8_t mode) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(15,20);
  switch (mode) {
    case 0: display.print(F("Plate")); break;
    case 1: display.print(F("Hall")); break;
  }

  display.setFont(&Dungeon12pt7b);
  display.setCursor(10,50);
  display.print(F("Reverb"));

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showPhaserModeOnScreen(uint8_t screen, uint8_t mode, uint8_t stages) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10,20);
  display.print(stages);
  display.print(F("x"));

  switch (mode) {
    case 0: display.print(F("Mono")); break;
    case 1: display.print(F("Stereo")); break;
    case 2: display.print(F("Cross")); break;
  }

  display.setFont(&Dungeon12pt7b);
  display.setCursor(10,50);
  display.print(F("Phaser"));

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showChorusModeOnScreen(uint8_t screen, uint8_t mode) {
  display.clearDisplay();
  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(15,20);
  switch (mode/2) {
    case 0: display.print(F("Long")); break;
    case 1: display.print(F("Short")); break;
  }

  display.setFont(&Dungeon12pt7b);
  display.setCursor(10,50);
  switch (mode%2) {
    case 0: display.print(F("Chorus")); break;
    case 1: display.print(F("Flanger")); break;
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showTimeTempoOnScreen(uint8_t screen, uint8_t time, uint8_t tempo) {
  display.clearDisplay();

  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,20);
  display.print(F("Time "));
  display.print(time);

  display.setCursor(0,40);
  display.print(F("Tempo "));
  display.print(tempo);

    TCA9548A(SCRMAP[screen]);
    display.display();
}

void showMulDivTempoOnScreen(uint8_t screen, uint8_t mul, uint8_t div) {
  display.clearDisplay();

  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,20);
  display.print(F("Mul "));
  display.print(mul);

  display.setCursor(0,40);
  display.print(F("Div "));
  display.print(div);

    TCA9548A(SCRMAP[screen]);
    display.display();
}

void showLRPhaseOnScreen(uint8_t screen, uint8_t lrphase, uint8_t offset, bool showOffset) {
  display.clearDisplay();
  display.drawCircle(31,31,PIERADIUS,SSD1306_WHITE);

  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(55,15);
  display.print(lrphase*90/128); //128 = 90 degree phase difference, so 0 = 0 degree phase difference and 255 = about 180 degrees phase difference

  if (showOffset) {
    display.setCursor(60,60);
    display.print(offset);
    display.print(F("Hz"));
  }
}

void showPhaseOnScreen(uint8_t screen, uint8_t phase, uint8_t sync) {
  display.clearDisplay();

  display.drawCircle(31,31,PIERADIUS,SSD1306_WHITE);
  drawPie(31,31,phase);

  display.setFont(&Dungeon9pt7b);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(55,15);
  display.print(90*phase);

  display.setCursor(70,45);
  if (sync==1) {
    display.print(F("sync"));
  } else {
    display.print(F("free"));
  }

  TCA9548A(SCRMAP[screen]);
  display.display();
}

//Draws a filled pie with radius 20 for phase 0-180 degree
void drawPiePart(uint8_t cx, uint8_t cy, uint8_t phase) {
  //TODO
}

//Draws a filled pie with radius 20 for phases 0, 1 (=90), 2 (=180) or 3 (=270)
void drawPie(uint8_t cx, uint8_t cy, uint8_t phase) {
  for (uint8_t y = 0; y<PIERADIUS; y++) {
    uint8_t x = 0;
    if (phase>0) {
      x = PIEPOS[y];
    }
    display.drawLine(cx,cy+y-PIERADIUS,cx+x,cy+y-PIERADIUS,SSD1306_WHITE);
    if (phase>1) {
      if (phase==3) {
        display.drawLine(cx-x,cy+PIERADIUS-y-1,cx+x,cy+PIERADIUS-y-1,SSD1306_WHITE);
      } else {
        display.drawLine(cx,cy+PIERADIUS-y-1,cx+x,cy+PIERADIUS-y-1,SSD1306_WHITE);
      }
    }
  }
}

void showEnvelopeOnScreen(uint8_t screen, uint8_t op, const env_type& env, bool activeScreen, uint8_t param, bool balanced, uint8_t range) {
  display.clearDisplay();
  showEnvelope(40,20,env);

  if (activeScreen) {
    display.setFont(&Dungeon9pt7b);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,12);
    switch (op) {
      case 0: display.print(F("Attack")); break;
      case 1: display.print(F("Decay-1")); break;
      case 2: display.print(F("Decay-2")); break;
      case 3: break;
      case 4: display.print(F("Rel-1")); break;
      case 5: display.print(F("Rel-2")); break;
      case 6: display.print(F("Delay")); break;
      case 7: display.print(F("Attack")); break;
      case 8: display.print(F("Decay-1")); break;
      case 9: display.print(F("Decay-2")); break;
      case 10: display.print(F("Sustain")); break;
      case 11: display.print(F("Rel-1")); break;
      case 12: display.print(F("Rel-2")); break;
      case 13: display.print(F("Rate")); break;
      case 14: display.print(F("Range")); break;
    }
    if (op!=3) {
      if (balanced) {
        drawNumber(param-128,127,12);
      } else {
        drawNumber(param,127,12);
      }
    }
  }

  if (env.level[3]<130) {
    display.setCursor(50,30);
  } else {
    display.setCursor(50,63);
  }
  display.print(F("+"));
  display.print(range);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

//Shows a rectangle at the screen's border
void showScreenBorder(uint8_t screen) {
  display.clearDisplay();
  display.drawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SSD1306_WHITE);

  TCA9548A(SCRMAP[screen]);
  display.display();
}

void showEnvelope(uint8_t envheight, uint8_t envpos, const env_type& env) {
  float x1,x2,y1,y2,yd,yq,xq,r0,r1,r2,r3,r4,r5,l0,l1,l2,l3,l4,l5;
  //Getting envelope parameters
  r0 = env.rate[0];
  r1 = 255 - env.rate[1];
  r2 = 255 - env.rate[2];
  r3 = 255 - env.rate[3];
  r4 = 255 - env.rate[4];
  r5 = 255 - env.rate[5];
  l0 = env.level[0];
  l1 = env.level[1];
  l2 = env.level[2];
  l3 = env.level[3];
  l4 = env.level[4];
  l5 = env.level[5];
  yq = envheight/255.0; //Quotient bij maximale waarde van 63
  xq = 127.0 / (255 + (r0>0 ? 255 : 0) + (r1>0 ? 255 : 0) + (r2>0 ? 255 : 0 ) + (r3>0 ? 255 : 0) + (r4>0 ? 255 : 0) + (r5>0 ? 255 : 0));
  yd = envpos;
  x1 = 0.0;
  x2 = x1 + xq*r0; //Delay
  y1 = yq*(255 - l0)+yd;
  y2 = yq*(255 - l0)+yd;
  display.drawLine(x1,y1,x2,y2,SSD1306_WHITE);
  x1 = x2;
  y1 = y2;
  x2 = x1 + xq*r1; //Attack
  y2 = yq*(255 - l1)+yd;
  display.drawLine(x1,y1,x2,y2,SSD1306_WHITE);
  x1 = x2;
  y1 = y2;
  x2 = x1 + xq*r2; //Decay-1
  y2 = yq*(255 - l2)+yd;
  display.drawLine(x1,y1,x2,y2,SSD1306_WHITE);
  x1 = x2;
  y1 = y2;
  x2 = x1 + xq*r3; //Decay-2
  y2 = yq*(255 - l3)+yd;
  display.drawLine(x1,y1,x2,y2,SSD1306_WHITE);
  x1 = x2;
  y1 = y2;
  x2 = x1 + 127 - xq*(r0 + r1 + r2 + r3 + r4 + r5); //Sustain
  y2 = yq*(255 - l3)+yd;
  display.drawLine(x1,y1-1,x2,y2-1,SSD1306_WHITE);
  display.drawLine(x1,y1,x2,y2,SSD1306_WHITE);
  display.drawLine(x1,y1+1,x2,y2+1,SSD1306_WHITE);
  x1 = x2;
  y1 = y2;
  x2 = x1 + xq*r4; //Release-1
  y2 = yq*(255 - l4)+yd;
  display.drawLine(x1,y1,x2,y2,SSD1306_WHITE);
  x1 = x2;
  y1 = y2;
  x2 = x1 + xq*r5; //Release-2
  y2 = yq*(255 - l5)+yd;
  display.drawLine(x1,y1,x2,y2,SSD1306_WHITE);
}

void drawNumber(int16_t number, uint8_t x, uint8_t y)
{
  display.setCursor(x - getNumberWidth(number),y);
  display.print(number);
}

uint16_t getNumberWidth(int16_t number) {
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(number, 0, 20, &x1, &y1, &w, &h); //calc width of new string
  return w;
}

uint16_t getStringWidth(const String& str) {
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(str, 0, 20, &x1, &y1, &w, &h); //calc width of new string
  return w;
}

void drawPercentbar(int x,int y, int width,int height, uint8_t progress) {
  float bar = ((float)(width-4) / 255) * progress;

  display.drawRect(x, y, width, height, WHITE);
  // Display progress text
  if (height>25) {
    display.setFont(&Dungeon12pt7b);
    display.setCursor((width/2) -24, y+21 );
  } else {
    display.setFont(&Dungeon9pt7b);
    display.setCursor((width/2) -8, y+15 );
  }
  display.setTextColor(WHITE);
  display.print(progress);
  // Bar, inverse: switch colors at text position
  display.fillRect(x+2, y+2, bar , height-4, SSD1306_INVERSE);
}

//Low-level function for TCA9548A multiplex switch
void TCA9548A(uint8_t bus) {
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}
