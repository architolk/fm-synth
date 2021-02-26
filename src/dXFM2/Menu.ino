/*
*  Module for the parameter menu
*
*  this module is about handling the parameter menu (encoders 7 and 8)
*
*/

#define MENUCOUNT 6
const String MENUNAMES[MENUCOUNT] = {
  "Initialize",
  "Algorithm",
  "DX7 Patch",
  "MIDI",
  "Param",
  "LEDs"
};
const uint8_t MENUMAX[MENUCOUNT] = {0,31,31,0,0,0}; //Max values for a specific menu
uint8_t paramData[MENUCOUNT];

void setupMenu() {
  for (uint8_t param=0; param<MENUCOUNT; param++) {
    paramData[param] = 0;
  }
}

void showParamMenu(uint8_t param, uint8_t value) {
  switch (param) {
    case 2: showParamMenuOnScreen(param,MENUNAMES[param],getPatchName(value),6); break;
    default: showParamMenuOnScreen(param,MENUNAMES[param],"",6); break;
  }
}

void executeParamMenu(uint8_t param, uint8_t value) {
  //Debug
  switch (param) {
    case 0: executeInit(); break;
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

uint8_t getMenuParamdata(uint8_t param) {
  return paramData[param];
}

void setMenuParamdata(uint8_t param, uint8_t value) {
  paramData[param] = value;
}

uint8_t getMenuMaxValue(uint8_t param) {
  return MENUMAX[param];
}
