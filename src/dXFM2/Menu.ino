/*
*  Module for the parameter menu
*
*  this module is about handling the parameter menu (encoders 7 and 8)
*
*/

#define MENUCOUNT 8
const String MENUNAMES[MENUCOUNT] = {
  "Initialize",
  "Algo",
  "DX7 Patch",
  "MIDI",
  "Params A",
  "Params B",
  "LEDs",
  "Synth mode"
};
const uint8_t MENUMAX[MENUCOUNT] = {0,31,31,0,255,255,0,1}; //Max values for a specific menu
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
    case 4: showParamValueMenuOnScreen(param,MENUNAMES[param],0,value,getParamValueQuick({0,value}),6); break;
    case 5: showParamValueMenuOnScreen(param,MENUNAMES[param],256,value,getParamValueQuick({0,256+value}),6); break;
    case 7: showParamMenuOnScreen(param,MENUNAMES[param],value==0 ? F("XFM2") : F("DX7"),6); break;
    default: showParamMenuOnScreen(param,MENUNAMES[param],"",6); break;
  }
}

void executeParamMenu(uint8_t param, uint8_t value) {
  //Debug
  switch (param) {
    case 0: executeInit(); break;
    case 1: setAlgorithm(value); break;
    case 2: activatePatch(value); break;
    case 7: setSynthMode(value); break;
    default: showDebug(value); break;
  }
}

void executeInit() {
  clearAlgoLEDs(); //Algorithm LEDs will be off during init process
  showMessage(6,F("Init dXFM2"));
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
  clearAlgoLEDs(); //Algorithm LEDs will be off during loading process
  showMessage(6,F("DX7 Mode!"));
  loadDefaultPatch(0,patch);
  xfm2PushActiveProgram(0);
  updateLEDs();
  patchChanged = true;
  doMenuChange();
}

void setAlgorithm(uint8_t algo) {
  //Only unit 0 supported
  showMessage(6,F("Algorithm"));
  xfm2SetAlgorithm(0,algo);
  updateLEDs();
  patchChanged = true;
  doMenuChange();
}

void setSynthMode(uint8_t mode) {
  //In DX7 mode, all parameter values are displayed like the DX7, so its easier to compare DX7 patches
  //Warning: doing this, you can't tell what is the actual value, and some small changes might not be visible
  //Also: at this moment, it doesn't compensate for differences in the engine between XFM2 and DX7
  if (mode==0) {
    showMessage(6,F("XFM2 mode"));
    dx7LegacyMode = false;
  } else {
    showMessage(6,F("DX7 mode"));
    dx7LegacyMode = true;
  }
  delay(1000);
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
