/*
*  Module for the parameter menu
*
*  this module is about handling the parameter menu (encoders 7 and 8)
*
*/

#define MENUCOUNT 5
const String MENUNAMES[5] = {
  "Initialize",
  "Algorithm",
  "MIDI",
  "Param",
  "LEDs"
};

void showParamMenu(uint8_t param) {
  showParamMenuOnScreen(param % MENUCOUNT,MENUNAMES[param % MENUCOUNT],6);
}

void executeParamMenu(uint8_t param, uint8_t value) {
  //Debug
  switch (param) {
    case 0: executeInit(); break;
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
