/*
*  Module for the Parameters
*
*  this module contains all parameters for the XFM2 synth
*
*/
const uint16_t PARAMMAP[6][6][7] PROGMEM = {
  { //0 & 8, LFO
    {153,151,152,154,149,150,180},
    {57,58,59,60,61,62,180},
    {45,46,47,48,49,50,180},
    {1000,1001,1002,1003,1004,1005,180},
    {222,223,224,225,226,227,180},
    {159,160,161,162,163,164,180}
  },
  { //1 & 7, Oscillators
    {236,237,238,239,240,241,180},
    {280,281,282,283,284,285,0},
    {268,269,270,271,272,273,0},
    {286,287,288,289,290,291,0},
    {134,135,136,0,137,208,206},
    {205,130,131,132,133,207,146}
  },
  {  //2 & 6, Operators
    {33,34,35,36,37,38,180},
    {1012,1013,1014,1015,1016,1017,180},
    {2006,2007,2008,2009,2010,2011,180},
    {7,8,9,10,11,12,180},
    {3103,3110,3117,0,3124,3199,3187},
    {3181,3075,3082,3089,3096,3193,3140}
  },
  { //3 & 5, Effects
    {0,330,332,331,0,333,0},
    {301,1018,305,306,304,1019,300},
    {311,314,313,1020,315,318,310},
    {391,393,392,394,0,0,390},
    {361,363,364,362,365,366,360},
    {0,370,320,321,380,410,180}
  },
  { //4, Master
    {221,174,228,230,229,251,1027},
    {0,0,0,0,0,0,0},
    {39,40,41,42,43,44,242},
    {39,40,41,42,43,44,242},
    {1021,1022,1023,1024,1025,1026,180},
    {1021,1022,1023,1024,1025,1026,180}
  },
  { //5, LEDs
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6}
  }
};
const uint16_t PARAMEXMAP[28][2] PROGMEM = {
  {51,63},{52,64},{53,65},{54,66},{55,67},{56,68}, //LFO 1000-1005
  {27,14},{28,14},{29,14},{30,14},{31,14},{32,14}, //OPS 2006-2011
  {15,21},{16,22},{17,23},{18,24},{19,25},{20,26}, //OPS 1012-1017
  {303,307},{308,309},{31,317}, //EFX 1018-1020
  {256,257},{258,259},{260,261},{262,263},{264,265},{266,267}, //MASTER 1021-1026
  {411,412} //MASTER 1027
};

//Maximum values for every parameter
const uint8_t PARAMMAX[512] PROGMEM = {
  0,0,0,0,0,0,0, //Param zero and algorithms
  255,255,255,255,255,255, //Feedback
  0,0, //Oscillator sync and mode
  255,255,255,255,255,255, //Ratio
  255,255,255,255,255,255, //Ratio fine
  255,255,255,255,255,255, //Fine
  255,255,255,255,255,255, //Level
  255,255,255,255,255,255, //Velo sensitivity
  255,255,255,255,255,255, //Key Breakpoint
  255,255,255,255,255,255, //Key left depth
  255,255,255,255,255,255, //Key right depth
  3,3,3,3,3,3, //Key left curve
  3,3,3,3,3,3, //Key right curve
  255,255,255,255,255,255,0, //Envelope L1
  255,255,255,255,255,255,0, //Envelope L2
  255,255,255,255,255,255,0, //Envelope L3
  255,255,255,255,255,255,0, //Envelope L4
  255,255,255,255,255,255,0, //Envelope R1
  255,255,255,255,255,255,0, //Envelope R2
  255,255,255,255,255,255,0, //Envelope R3
  255,255,255,255,255,255, //Envelope R4
  255,255,255,255, //Pitch envelope L1,L2,L3,L4
  255,255,255,255, //Pitch envelope R1,R2,R3,R4
  255,255, //Pitch envelope range and velocity (in octaves, so 255 is probably a bit to much?)
  255,255,255,255,255,255, //Envelope rate
  255,0,0, //Pitch envelope rate
  255, //LFO Pitch depth
  255, //LFO Amplitude depth
  255, //LFO Speed
  3, //LFO Sync
  5, //LFO Wave
  255, //LFO Fade
  255,255,255,255, //LFO Wheels
  255,255,255,255,255,255, //LFO AMS
  0,0,0,0,0,0,0,255,255, //LFO Bend
  255, //Transpose. Center is 24, so probably 48 max?
  0,0,0,0,0,255, //Volume
  255,255,255,255,255,255, //Envelope L0
  255,255,255,255,255,255, //Envelope R0
  255,255,255,255,255,255, //Envelope L5
  255,255,255,255,255,255, //Envelope R5
  255,255,255,255, //Pitch envelope L0, R0, L5, R5
  255,255,255,255, //LFO Wheels
  255,255,255,255, //Volume Wheels
  255,255,255,255, //Pitch Wheels
  255, //Pan
  255,255,255,255,255,255, //LFO PMS
  1, //Legato
  2, //Portamento mode
  255, //Portamento time
  0,0,0,0,0, //NOP
  7,7,7,7,7,7, //Wave forms oscillator #1
  255, //Velocity offset
  0, //Velocity curve (not specified in the documentation)
  0,0,0, //EG Loop, loop_seg and restart
  0,0,0,0,255,0,0,0,0, //Tuning
  255,255,255,255,255,255,255,255,255,255,255,255, //Levels left & right
  7,7,7,7,7,7, //Wave forms oscillator #2
  1,1,1,1,1,1, //Wave mode
  255,255,255,255,255,255, //Wave ratio
  3,3,3,3,3,3, //Oscillator phase
  0,0,0,0,0,0,0,0, //NOP
  255,255, //Delay dry & wet
  2, //Delay mode
  255,255,255,255, //Delay time, feedback, lo, hi
  255, //Delay tempo (minimum value = 50!)
  255,255, //Delay multiplier and divider
  255,255, //Phaser wet & dry
  2, //Phaser mode
  255,255,255,255, //Phaser depth, speed, feedback, offset
  12, //Phaser stages (minimum value = 4!)
  255, //Phaser LR phase
  0, //Phaser waveform (not specified in the documentation)
  255,255,0,0,0,0,0,0,0,0, //Filter LO & HI
  255,255,255,255,0,0,0,0,0,0, //Amplitude modulation
  0,0,0,0,0,0,0,0,0,0, //FIR (not specified in the documentation)
  0,0,0,0,0,0,0,0,0,0, //Waveshaper (not specified in the documentation)
  255,255, //Chorus wet & dry
  3, //Chorus mode
  255,255,255,255,0,0,0, //Chorus speed, depth, feedback, phase
  255,0,0,0,0,0,0,0,0,0, //Decimator depth
  255,0,0,0,0,0,0,0,0,0, //Bitcrusher depth
  255,255, //Reverb wet & dry
  1, //Reverb mode
  255,255, //Reverb decay, damp
  0,0,0, //Reverb D0,D1,D2 (not specified in the documentation)
  0,0, //Reverb NOP
  0,0,0,0,0,0,0,0,0,0, //NOP 400-409
  1, //EFX Routing
  255, //Output
  3, //Gain
  0,0,0,0,0,0,0, //NOP
  255,255,255,255,255,255,255,255,0,0, //Performance controls min & max
  0,0,0,0,0,0,0,0,0,0, //NOP 430-439
  0,0,0,0,0,0,0,0,0,0, //NOP 440-449
  5, //ARP mode
  255, //ARP tempo (minimum value = 50!)
  255, //ARP tempo fine (not specified in the documentation)
  255, //ARP tempo multiplicator
  255, //ARP octaves
  0,0,0,0,0, //ARP NOP
  0,0,0,0,0,0,0,0,0,0, //NOP 460-469
  0,0,0,0,0,0,0,0,0,0, //NOP 470-479
  0,0,0,0,0,0,0,0,0,0, //NOP 480-489
  0,0,0,0,0,0,0,0,0,0, //NOP 490-499
  0,0,0,0,0,0,0,0,0,0,0,0 //NOP 500-511
};

uint8_t paramValue[2][512]; //Parameter 0 doesn't exists, but nr 512 does, so we need an array of 513 items

void setupParams() {
  for (uint8_t unit=0; unit<2; unit++) {
    for (uint16_t param=0; param<512; param++) {
      paramValue[unit][param] = 0;
    }
  }
  //Setting some particular parameter values for testing:
  //Algo & feedback
  /*
  paramValue[0][1] = 5; //Operator 1 is carrier and modulated by operator 2
  paramValue[0][2] = 0; //Operator 2 is modulator
  paramValue[0][3] = 17;//Operator 3 is carrier and modulated by operator 4
  paramValue[0][4] = 0; //Operator 4 is modulator
  paramValue[0][5] = 33;//Operator 5 is carrier and modulated by itself (feedback)
  paramValue[0][6] = 0; //Operator 6 is modulator (but doesn't modulates anything)
  */
  paramValue[0][5] = 33;//Operator 5 is carrier and modulated by itself (feedback)
  paramValue[0][11] = 250; //Feedback of operator 5 (other operators don't have feedback)
  //Level and volume
  paramValue[0][33] = 255;
  paramValue[0][34] = 220;
  paramValue[0][35] = 255;
  paramValue[0][36] = 180;
  paramValue[0][37] = 220;
  paramValue[0][38] = 255;
  paramValue[0][180] = 200;
  //Ratio
  paramValue[0][15] = 1;
  paramValue[0][16] = 1;
  paramValue[0][17] = 1;
  paramValue[0][18] = 16;
  paramValue[0][19] = 1;
  paramValue[0][20] = 1;
  //Ratio fine
  paramValue[0][21] = 0;
  paramValue[0][22] = 0;
  paramValue[0][23] = 0;
  paramValue[0][24] = 0;
  paramValue[0][25] = 0;
  paramValue[0][26] = 0;
  //Fine
  paramValue[0][27] = 128;
  paramValue[0][28] = 128;
  paramValue[0][29] = 128;
  paramValue[0][30] = 128;
  paramValue[0][31] = 128;
  paramValue[0][32] = 128;
  //Envelope level and rate for operator 0
  paramValue[0][181] = 0;
  paramValue[0][75] = 255;
  paramValue[0][82] = 255;
  paramValue[0][89] = 255;
  paramValue[0][96] = 0;
  paramValue[0][193] = 0;
  paramValue[0][187] = 0;
  paramValue[0][103] = 230;
  paramValue[0][110] = 255;
  paramValue[0][117] = 255;
  paramValue[0][124] = 160;
  paramValue[0][199] = 255;
  //Master levels
  paramValue[0][411] = 200;
  paramValue[0][412] = 2;
}

param_type getParam(uint8_t green, uint8_t blue, uint8_t selOp, uint8_t usedOp, uint8_t toggle) {
  uint8_t menu = green;
  uint8_t unit = 0;
  if (greenSelect>4) {
    menu = 8-green;
    unit = 1;
  }
  uint16_t val = PARAMMAP[menu][blue][usedOp];
  if (val>3000) {
    return {unit,val-3000+selOp};
  } else {
    if (val>1999) {
      return {unit,PARAMEXMAP[val-2000][toggle]};
    } else {
      if (val>999) {
        return {unit,PARAMEXMAP[val-1000][toggle]};
      } else {
        return {unit,val};
      }
    }
  }
}

uint8_t getParamType(uint8_t green, uint8_t blue, uint8_t selOp, uint8_t usedOp, uint8_t toggle) {
  uint8_t menu = green;
  uint8_t unit = 0;
  if (greenSelect>4) {
    menu = 8-green;
    unit = 1;
  }
  uint16_t val = PARAMMAP[menu][blue][usedOp];
  if (val>3000) {
    return 3;
  } else {
    if (val>1999) {
      return 2;
    } else {
      if (val>999) {
        return 1;
      } else {
        return 0;
      }
    }
  }
}

uint8_t getParamMax(uint8_t green, uint8_t blue, uint8_t selOp, uint8_t usedOp, uint8_t toggle) {
  param_type param = getParam(green,blue,selOp,usedOp,toggle);
  return PARAMMAX[param.param];
}

uint8_t getParamValue(uint8_t green, uint8_t blue, uint8_t selOp, uint8_t usedOp, uint8_t toggle) {
  param_type param = getParam(green,blue,selOp,usedOp,toggle);
  return paramValue[param.unit][param.param];
}

uint8_t getParamValueQuick(param_type param) {
  return paramValue[param.unit][param.param];
}

void setParamValue(uint8_t green, uint8_t blue, uint8_t selOp, uint8_t usedOp, uint8_t toggle, uint8_t value) {
  param_type param = getParam(green,blue,selOp,usedOp,toggle);
  paramValue[param.unit][param.param] = value;
}

void toggleParamValueBit(uint8_t green, uint8_t blue, uint8_t selOp, uint8_t usedOp, uint8_t toggle, uint8_t bitnr) {
  param_type param = getParam(green,blue,selOp,usedOp,toggle);
  if (bitRead(paramValue[param.unit][param.param],bitnr)==0) {
    bitWrite(paramValue[param.unit][param.param],bitnr,1);
  } else {
    bitWrite(paramValue[param.unit][param.param],bitnr,0);
  }
}

void toggleLEDParamValueBit(uint8_t menu, uint8_t btn) {
  //TODO: Serial communication to XFM2 for this...
  if (menu==6) {
    toggleParamValueBit(5,0,0,btn,0,0);
  } else {
    toggleParamValueBit(5,0,0,menu,0,btn+1);
  }
}

bool getParamValueBit(uint8_t green, uint8_t blue, uint8_t selOp, uint8_t usedOp, uint8_t toggle, uint8_t bitnr) {
  param_type param = getParam(green,blue,selOp,usedOp,toggle);
  return (bitRead(paramValue[param.unit][param.param],bitnr)==1);
}
