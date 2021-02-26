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

void showParamMenu(uint8_t param) {
  switch (param) {
    3: showParamMenuOnScreen(param % MENUCOUNT,MENUNAMES[param % MENUCOUNT],getPatchName(0),6); break;
    default: showParamMenuOnScreen(param % MENUCOUNT,MENUNAMES[param % MENUCOUNT],"",6); break;
  }
}

void executeParamMenu(uint8_t param, uint8_t value) {
  //Debug
  switch (param) {
    case 0: executeInit(); break;
    case 2: activatePatch(); break;
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

void activatePatch() {
  //Something..
}
