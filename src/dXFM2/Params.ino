/*
*  Module for the Parameters
*
*  this module contains all parameters for the XFM2 synth
*
*/
const uint16_t PARAMMAP[5][6][7] PROGMEM = {
  { //0 & 8, LFO
    {159,160,161,162,163,164,180},
    {222,223,224,225,226,227,180},
    {1000,1001,1002,1003,1004,1005,180},
    {45,46,47,48,49,50,180},
    {57,58,59,60,61,62,180},
    {153,151,152,154,149,150,180}
  },
  { //1 & 7, Oscillators
    {205,130,131,132,133,207,146},
    {134,135,136,0,137,208,206},
    {286,287,288,289,290,291,0},
    {268,269,270,271,272,273,0},
    {280,281,282,283,284,285,0},
    {236,237,238,239,240,241,180}
  },
  {  //2 & 6, Operators
    {3181,3075,3082,3089,3096,3193,3140},
    {3103,3110,3117,0,3124,3199,3187},
    {7,8,9,10,11,12,0},
    {2006,2007,2008,2009,2010,2011,0},
    {1012,1013,1014,1015,1016,1017,0},
    {33,34,35,36,37,38,180}
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
    {1021,1022,1023,1024,1025,1026,180},
    {1021,1022,1023,1024,1025,1026,180},
    {39,40,41,42,43,44,242},
    {39,40,41,42,43,44,242},
    {0,0,0,0,0,0,0},
    {221,174,228,230,229,251,1027}
  }
};
const uint16_t PARAMEXMAP[28][2] = {
  {51,63},{52,64},{53,65},{54,66},{55,67},{56,68}, //LFO 1000-1005
  {27,14},{28,14},{29,14},{30,14},{31,14},{32,14}, //OPS 2006-2011
  {15,21},{16,22},{17,23},{18,24},{19,25},{20,26}, //OPS 1012-1017
  {303,307},{308,309},{31,317}, //EFX 1018-1020
  {256,257},{258,259},{260,261},{262,263},{264,265},{266,267}, //MASTER 1021-1026
  {411,412} //MASTER 1027
}

uint8_t paramValue[2][500];

typedef struct {
  uint8_t unit; //the unit that is selected
  uint8_t param; //the parameter that is selected
} param_type;

param_type getParam(uint8_t green, uint8_t blue, uint8_t operator, uint8_t toggle) {
  uint8_t menu = green;
  uint8_t unit = 0;
  if (greenSelect>4) {
    menu = 8-green;
    unit = 1;
  }
  uint16_t param = PARAMMAP[menu,blue,operator];
  if (param>3000) {
    return {unit,param-3000+operator};
  } else {
    if (param>1999) {
      return {unit,PARAMEXMAP[param-2000][toggle]};
    } else {
      if (param>999) {
        return {unit,PARAMEXMAP[param-1000][toggle]};
      } else {
        return {unit,param};
      }
    }
  }
}

uint8_t getParamValue(uint8_t green, uint8_t blue, uint8_t operator, uint8_t toggle) {
  param_type param = getParam(green,blue,operator,toggle);
  return paramValue[param.unit][param.param];
}

setParamValue(uint8_t green, uint8_t blue, uint8_t operator, uint8_t toggle, uint8_t value) {
  param_type param = getParam(green,blue,operator,toggle);
  paramValue[param.unit][param.param] = value;
}
