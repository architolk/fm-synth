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
    {1028,1029,1030,1031,1032,1033,180},
    {268,269,270,271,272,273,180},
    {2040,2041,2042,2043,2044,2045,180},
    {134,135,136,0,137,208,206},
    {205,130,131,132,133,207,138}
  },
  {  //2 & 6, Operators
    {33,34,35,36,37,38,180},
    {1012,1013,1014,1015,1016,1017,180},
    {2006,2007,2008,2009,2010,2011,180},
    {3034,3035,3036,3037,3038,3039,180},
    {4103,4110,4117,0,4124,4199,4187},
    {4181,4075,4082,4089,4096,4193,4140}
  },
  { //3 & 5, Effects
    {0,380,370,321,320,410,0},
    {366,362,365,364,363,361,360},
    {0,392,0,394,393,391,390},
    {318,1020,315,313,314,311,310},
    {1019,1018,305,306,304,301,300},
    {331,333,0,332,330,0,0}
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
const uint16_t PARAMEXMAP[46][2] PROGMEM = {
  {51,63},{52,64},{53,65},{54,66},{55,67},{56,68}, //LFO 1000-1005
  {27,14},{28,14},{29,14},{30,14},{31,14},{32,14}, //OPS 2006-2011
  {15,21},{16,22},{17,23},{18,24},{19,25},{20,26}, //OPS 1012-1017
  {302,307},{308,309},{312,317}, //EFX 1018-1020
  {256,257},{258,259},{260,261},{262,263},{264,265},{266,267}, //MASTER 1021-1026
  {411,412}, //MASTER 1027
  {280,274},{281,275},{282,276},{283,277},{284,278},{285,279}, //OSC 1028-1033
  {7,1},{8,2},{9,3},{10,4},{11,5},{12,6}, //OPS 3034-3039
  {286,13},{287,13},{288,13},{289,13},{290,13},{291,13} //OSC 2040 - 2045
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
  0,0,0, //EG Loop, loop_seg and restart (restart is not specified in the documention, but is available in the spreadsheet)
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
  255,255, //Phaser dry & wet
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

//Default values for every parameter
const uint8_t PARAMDEFAULT[512] PROGMEM = {
  0,1,0,0,0,0,0, //Operator 1 is carrier. All other operators are off and no modulation. No self-modulation (feedback)
  0,0,0,0,0,0, //Feedback levels all zero
  0,0, //Oscillator sync and mode
  1,1,1,1,1,1, //Ratio, all default to 1:1
  0,0,0,0,0,0, //Ratio fine
  128,128,128,128,128,128, //Percentage operator ajustment (128 = 0%)
  200,200,200,200,200,200, //Level
  200,200,200,200,200,200, //Velo sensitivity
  60,60,60,60,60,60, //Key Breakpoint (60 = C4 = middle C)
  0,0,0,0,0,0, //Key left depth
  0,0,0,0,0,0, //Key right depth
  0,0,0,0,0,0, //Key left curve
  0,0,0,0,0,0, //Key right curve
  255,255,255,255,255,255,0, //Envelope L1 (end of attack)
  255,255,255,255,255,255,0, //Envelope L2 (end of decay-1)
  255,255,255,255,255,255,0, //Envelope L3 (sustain level)
  0,0,0,0,0,0,0, //Envelope L4 (end of release-1)
  255,255,255,255,255,255,0, //Envelope R1 (attack rate, very fast)
  255,255,255,255,255,255,0, //Envelope R2 (decay-1 rate, very fast - doesn't do anything: L2=L1)
  255,255,255,255,255,255,0, //Envelope R3 (decay-2 rate, very fast - doesn't do anything: L3=L2=L1)
  255,255,255,255,255,255, //Envelope R4 (release-1 rate, very fast)
  128,128,128,128, //Pitch envelope L1,L2,L3,L4 (-127 to 127 levels, 128 is zero pitch change)
  255,255,255,255, //Pitch envelope R1,R2,R3,R4 (very fast rates)
  0,0, //Pitch envelope range and velocity set to zero
  0,0,0,0,0,0, //Envelope rate set to zero for all operators
  0,0,0, //Pitch envelope rate set to zero
  30, //LFO Pitch depth (global)
  0, //LFO Amplitude depth
  100, //LFO Speed
  0, //LFO Sync
  0, //LFO Wave
  255, //LFO Fade
  30,0,30,255, //LFO Wheels
  255,255,255,255,255,255, //LFO AMS per operator (see also global setting)
  0,0,0,0,0,0,0,2,2, //LFO Bend
  12, //Transpose. Center is 24, so probably 48 max? (huh? so it is actually transposed 12 down???)
  0,0,0,0,0,200, //Volume
  0,0,0,0,0,0, //Envelope L0 (start of envelope)
  0,0,0,0,0,0, //Envelope R0 (delay)
  0,0,0,0,0,0, //Envelope L5 (end of envelope)
  255,255,255,255,255,255, //Envelope R5 (release-2 rate, very fast)
  128,0,128,255, //Pitch envelope L0, R0, L5, R5 (start level, delay, end level, release-2 rate: level 128 is zero pitch change)
  255,255,255,255, //LFO Wheels
  255,255,255,255, //Volume Wheels
  255,255,255,255, //Pitch Wheels
  128, //Pan (-127 to 127, 128 = pan to centre)
  0,0,0,0,0,0, //LFO PMS per operator (see also global setting)
  0, //Legato (default polyphonic)
  0, //Portamento mode (default off)
  0, //Portamento time
  0,0,0,0,0, //NOP
  0,0,0,0,0,0, //Wave forms oscillator #1 (set to sine wave)
  20, //Velocity offset
  0, //Velocity curve (not specified in the documentation)
  0,0,255, //EG Loop, loop_seg and restart
  0,0,0,0,0,0,0,0,0, //Tuning (defaults to chromatic)
  255,255,255,255,255,255,255,255,255,255,255,255, //Levels left & right
  0,0,0,0,0,0, //Wave forms oscillator #2 (set to sine wave)
  0,0,0,0,0,0, //Wave mode (only wave #1 active)
  1,1,1,1,1,1, //Wave ratio (all set to 1:1)
  0,0,0,0,0,0, //Oscillator phase (0 degree)
  0,0,0,0,0,0,0,0, //NOP
  255,0, //Delay dry & wet (no delay audiable)
  0, //Delay mode (default stereo)
  128,150,255,0, //Delay time, feedback, lo, hi
  50, //Delay tempo (minimum value = 50!) [weird: in the excel this is set to 0?]
  0,0, //Delay multiplier and divider
  255,0, //Phaser dry & wet (no phaser audiable)
  1, //Phaser mode (default stereo)
  30,30,0,128, //Phaser depth, speed, feedback, offset (offset probably -127 to 127??)
  4, //Phaser stages (minimum value = 4!)
  120, //Phaser LR phase
  0, //Phaser waveform (not specified in the documentation)
  255,0,0,0,0,0,0,0,0,0, //Filter LO & HI (lo pass cuttoff = 255, so nothing to cut, hi pass cuttoff = 0, so nothing to cut)
  10,0,0,120,0,0,0,0,0,0, //Amplitude speed, range, depth, LR phase (depth = 0, so no effect)
  0,0,0,0,0,0,0,0,0,0, //FIR (not specified in the documentation)
  0,0,0,0,0,0,0,0,0,0, //Waveshaper (not specified in the documentation)
  255,0, //Chorus dry & wet (no chorus audiable)
  0, //Chorus mode (long)
  50,30,0,128,0,0,0, //Chorus speed, depth, feedback, phase
  0,0,0,0,0,0,0,0,0,0, //Decimator depth (set to zero)
  0,0,0,0,0,0,0,0,0,0, //Bitcrusher depth (set to zero)
  255,0, //Reverb dry & wet (no reverb audiable)
  0, //Reverb mode (default plate)
  250,0, //Reverb decay, damp
  0,0,0, //Reverb D0,D1,D2 (not specified in the documentation)
  0,0, //Reverb NOP
  0,0,0,0,0,0,0,0,0,0, //NOP 400-409
  0, //EFX Routing
  200, //Output
  2, //Gain
  0,0,0,0,0,0,0, //NOP
  2,74,2,76,2,74,2,75,0,0, //Performance controls min & max
  0,0,0,0,0,0,0,0,0,0, //NOP 430-439
  0,0,0,0,0,0,0,0,0,0, //NOP 440-449
  0, //ARP mode
  50, //ARP tempo (minimum value = 50!)
  0, //ARP tempo fine (not specified in the documentation)
  0, //ARP tempo multiplicator
  0, //ARP octaves
  0,0,0,0,0, //ARP NOP
  0,0,0,0,0,0,0,0,0,0, //NOP 460-469
  0,0,0,0,0,0,0,0,0,0, //NOP 470-479
  0,0,0,0,0,0,0,0,0,0, //NOP 480-489
  0,0,0,0,0,0,0,0,0,0, //NOP 490-499
  0,0,0,0,0,0,0,0,0,0,0,0 //NOP 500-511
};

uint8_t paramValue[2][512];

void setupParams() {
  for (uint8_t unit=0; unit<2; unit++) {
    for (uint16_t param=0; param<512; param++) {
      paramValue[unit][param] = PARAMDEFAULT[param];
    }
  }
}

param_type getParam(uint8_t green, uint8_t blue, uint8_t selOp, uint8_t usedOp, uint8_t toggle) {
  uint8_t menu = green;
  uint8_t bmenu = blue;
  uint8_t unit = 0;
  if (green>4) {
    menu = 8-green;
    unit = 1;
  }
  if (blue==BLUE_LEDS) {
    menu = 5;
    bmenu = 0;
  }
  uint16_t val = PARAMMAP[menu][bmenu][usedOp];
  if (val>4000) {
    return {unit,val-4000+selOp};
  } else {
    if (val>2999) {
      return {unit,PARAMEXMAP[val-3000][toggle]};
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
}

uint8_t getParamType(uint8_t green, uint8_t blue, uint8_t selOp, uint8_t usedOp, uint8_t toggle) {
  uint8_t menu = green;
  uint8_t bmenu = blue;
  uint8_t unit = 0;
  if (green>4) {
    menu = 8-green;
    unit = 1;
  }
  if (blue==BLUE_LEDS) {
    menu = 5;
    bmenu = 0;
  }
  uint16_t val = PARAMMAP[menu][bmenu][usedOp];
  if (val>4000) {
    return 4;
  } else {
    if (val>2999) {
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
  if (menu==6) {
    toggleParamValueBit(greenSelect,BLUE_LEDS,0,btn,0,0);
  } else {
    toggleParamValueBit(greenSelect,BLUE_LEDS,0,menu,0,btn+1);
  }
}

bool getParamValueBit(uint8_t green, uint8_t blue, uint8_t selOp, uint8_t usedOp, uint8_t toggle, uint8_t bitnr) {
  param_type param = getParam(green,blue,selOp,usedOp,toggle);
  return (bitRead(paramValue[param.unit][param.param],bitnr)==1);
}
