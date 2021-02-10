/*
*  Module for the Menus
*
*  this module contains the code to setup a particular screen
*
*/
void showMenu() {
  switch (greenSelect) {
    case 0: showLFOMenu(); break;
    case 1: showOSCMenu(); break;
    case 2: showOPSMenu(); break;
    case 3: showEFXMenu(); break;
    case 4: showMasterMenu(); break;
    case 5: showEFXMenu(); break;
    case 6: showOPSMenu(); break;
    case 7: showOSCMenu(); break;
    case 8: showLFOMenu(); break;
  }
}

void showLFOMenu() {
  switch (blueSelect) {
    case 0: showAMS();
    case 1: showPMS();
    case 2: showKeyTracking();
    case 3: showKeyTracking();
    case 4: showKeyTracking();
    case 5: showLFO();
  }
}

void showOSCMenu() {
  switch (blueSelect) {
    case 0: showPitchEnvelope();
    case 1: showPitchEnvelope();
    case 2: showPhase();
    case 3: showWave(1);
    case 4: showOSCRatio();
    case 5: showWave(2);
  }
}

void showOPSMenu() {
  switch (blueSelect) {
    case 0: showAmplitudeEnvelope();
    case 1: showAmplitudeEnvelope();
    case 2: showFeedback();
    case 3: showPitch();
    case 4: showRatio();
    case 5: showLevel();
  }
}

void showEFXMenu() {
  //Nothing yet
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Effects"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showMasterMenu() {
  switch (blueSelect) {
    case 0: showMixer(0);
    case 1: showMixer(1);
    case 2: showVeloSense(0);
    case 3: showVeloSense(1);
    case 4: showMaster();
    case 5: showMaster();
  }
}

//
// LFO submenu
//
void showAMS() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("AMS"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showAMS() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("PMS"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showKeyTracking() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Tracking"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showLFO() {
  showParamValueOnScreen(F("LFO Wave"),0,getParam(greenSelect,blueSelect,0));
  showParamValueOnScreen(F("LFO Speed"),1,getParam(greenSelect,blueSelect,1));
  showParamValueOnScreen(F("LFO Sync"),2,getParam(greenSelect,blueSelect,2));
  showParamValueOnScreen(F("LFO Fade"),3,getParam(greenSelect,blueSelect,3));
  showParamValueOnScreen(F("LFO P.Depth"),4,getParam(greenSelect,blueSelect,4));
  showParamValueOnScreen(F("LFO A.Depth"),5,getParam(greenSelect,blueSelect,5));
  showParamValueOnScreen(F("Volume"),6,getParam(greenSelect,blueSelect,6));
}

//
// Oscillator submenu
//
void showPitchEnvelope() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Pitch Env"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showPhase() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Phase"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showWave(uint8_t widx) {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Wave"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showOSCRatio() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("OSC Ratio"),i,getParam(greenSelect,blueSelect,i));
  }
}

//
// Operator submenu
//
void showAmplitudeEnvelope() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Envelope"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showFeedback() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Feedback"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showPitch() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Pitch"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showRatio() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Ratio"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showLevel() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Level"),i,getParam(greenSelect,blueSelect,i));
  }
}

//
// Effects submenu
//

//
// Master submenu
//
void showMixer(uint8_t unit) {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Mixer"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showVeloSense(uint8_t unit) {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Velo sense"),i,getParam(greenSelect,blueSelect,i));
  }
}

void showMaster() {
  for (uint8_t i=0; i<7; i++) {
    showParamValueOnScreen(F("Master"),i,getParam(greenSelect,blueSelect,i));
  }
}
