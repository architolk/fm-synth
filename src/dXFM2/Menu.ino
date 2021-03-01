/*
*  Module for the parameter menu
*
*  this module is about handling the parameter menu (encoders 7 and 8)
*
*/

#define MENUCOUNT 7
const String MENUNAMES[MENUCOUNT] = {
  "Initialize",
  "Algo",
  "DX7 Patch",
  "MIDI",
  "Params 0-255",
  "Params 256-511",
  "LEDs"
};
const uint8_t MENUMAX[MENUCOUNT] = {0,31,31,0,255,255,0}; //Max values for a specific menu
uint8_t paramData[MENUCOUNT];

void setupMenu() {
  for (uint8_t param=0; param<MENUCOUNT; param++) {
    paramData[param] = 0;
  }
}

void showParamMenu(uint8_t param, uint8_t value) {
  switch (param) {
    case 1: showAlgorithmMenuOnScreen(param,MENUNAMES[param],value,6); break;
    case 2: showParamMenuOnScreen(param,MENUNAMES[param],getPatchName(value),6); break;
    case 4: showParamValueMenuOnScreen(param,MENUNAMES[param],0,value,getParamValueQuick({0,value}));
    case 5: showParamValueMenuOnScreen(param,MENUNAMES[param],256,value,getParamValueQuick({0,256+value}));
    default: showParamMenuOnScreen(param,MENUNAMES[param],"",6); break;
  }
}

void executeParamMenu(uint8_t param, uint8_t value) {
  //Debug
  switch (param) {
    case 0: executeInit(); break;
    case 1: setAlgorithm(value); break;
    case 2: activatePatch(value); break;
    default: showDebug(value); break;
  }
}

void executeInit() {
  showMessage(F("Init dXFM2"));
  if (xfm2InitPatch()) {
    if (xfm2GetActiveProgram(0)) {
      updateLEDs();
      patchChanged = true;
      doMenuChange();
    } else {
      showError(ERR_DUMP);
    }
  } else {
    showError(ERR_INIT);
  }
}

void activatePatch(uint8_t patch) {
  //Only unit 0 supported
  showMessage(F("DX7 Mode!"));
  loadDefaultPatch(0,patch);
  xfm2PushActiveProgram(0);
  updateLEDs();
  patchChanged = true;
  doMenuChange();
}

void setAlgorithm(uint8_t algo) {
  //Only unit 0 supported
  showMessage(F("Algorithm"));
  xfm2SetAlgorithm(0,algo);
  updateLEDs();
  patchChanged = true;
  doMenuChange();
}

uint8_t getMenuParamdata(uint8_t param) {
  return paramData[param];
}

void setMenuParamdata(uint8_t param, uint8_t value) {
  paramData[param] = value;
}

uint8_t getMenuMaxValue(uint8_t param) {
  return MENUMAX[param];
}
