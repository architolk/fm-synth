/*
*  Module for the Displays
*
*  this module contains the code to setup a particular display
*
*/
void showDisplay(uint8_t op) {
  switch (greenSelect) {
    case 0: showLFODisplay(op); break;
    case 1: showOSCDisplay(op); break;
    case 2: showOPSDisplay(op); break;
    case 3: showEFXDisplay(op); break;
    case 4: showMasterDisplay(op); break;
    case 5: showEFXDisplay(op); break;
    case 6: showOPSDisplay(op); break;
    case 7: showOSCDisplay(op); break;
    case 8: showLFODisplay(op); break;
  }
}

void showLFODisplay(uint8_t op) {
  switch (blueSelect) {
    case 0: showLFO(op); break;
    case 1: showKeyTracking(op); break;
    case 2: showKeyTracking(op); break;
    case 3: showKeyTracking(op); break;
    case 4: showPMS(op); break;
    case 5: showAMS(op); break;
  }
}

void showOSCDisplay(uint8_t op) {
  switch (blueSelect) {
    case 0: showWave(op,2); break;
    case 1: showOSCRatio(op); break;
    case 2: showWave(op,1); break;
    case 3: showPhase(op); break;
    case 4: showPitchEnvelope(op); break;
    case 5: showPitchEnvelope(op); break;
  }
}

void showOPSDisplay(uint8_t op) {
  switch (blueSelect) {
    case 0: showLevel(op); break;
    case 1: showRatioPitch(op); break;
    case 2: showRatioPitch(op); break;
    case 3: showFeedback(op); break;
    case 4: showAmplitudeEnvelope(op); break;
    case 5: showAmplitudeEnvelope(op); break;
  }
}

void showEFXDisplay(uint8_t op) {
  switch (blueSelect) {
    case 0: showEffectsDisplay(op); break;
    case 1: showChorusDisplay(op); break;
    case 2: showReverbDisplay(op); break;
    case 3: showPhaserDisplay(op); break;
    case 4: showDelayDisplay(op); break;
    case 5: showAMDisplay(op); break;
  }
}


void showAMDisplay(uint8_t op) {
  switch (op) {
    case 0: showValueOnScreen(F("Range"),0,getParamValue(greenSelect,blueSelect,operatorSelect,0,0)); break;
    case 1: showValueOnScreen(F("LR Phase"),1,getParamValue(greenSelect,blueSelect,operatorSelect,1,0)); break;
    case 2: showMessageOnScreen(2,F("AM")); break;
    case 3: showMessageOnScreen(3,F("AM")); break;
    case 4: showValueOnScreen(F("Speed"),4,getParamValue(greenSelect,blueSelect,operatorSelect,4,0)); break;
    case 5: showValueOnScreen(F("Depth"),5,getParamValue(greenSelect,blueSelect,operatorSelect,5,0)); break;
    case 6: showMessageOnScreen(6,F("AM")); break;
  }
}

void showDelayDisplay(uint8_t op) {
  switch (op) {
    case 0: showValueOnScreen(F("Ratio"),0,getParamValue(greenSelect,blueSelect,operatorSelect,0,0)); break;
    case 1: showDelayModeOnScreen(1,getParamValue(greenSelect,blueSelect,operatorSelect,1,0)); break;
    case 2: showValueOnScreen(F("Feedback"),2,getParamValue(greenSelect,blueSelect,operatorSelect,2,0)); break;
    case 3: showValueOnScreen(F("Hi pass"),3,getParamValue(greenSelect,blueSelect,operatorSelect,3,0)); break;
    case 4: showValueOnScreen(F("Lo pass"),4,getParamValue(greenSelect,blueSelect,operatorSelect,4,0)); break;
    case 5: showValueOnScreen(F("Wet"),5,getParamValue(greenSelect,blueSelect,operatorSelect,5,0)); break;
    case 6: showValueOnScreen(F("Dry"),6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0)); break;
  }
}

void showPhaserDisplay(uint8_t op) {
  switch (op) {
    case 0: showValueOnScreen(F("Phase"),0,getParamValue(greenSelect,blueSelect,operatorSelect,0,0)); break;
    case 1: showPhaserModeOnScreen(1,getParamValue(greenSelect,blueSelect,operatorSelect,1,0)); break;
    case 2: showValueOnScreen(F("Feedback"),2,getParamValue(greenSelect,blueSelect,operatorSelect,2,0)); break;
    case 3: showValueOnScreen(F("Depth"),3,getParamValue(greenSelect,blueSelect,operatorSelect,3,0)); break;
    case 4: showValueOnScreen(F("Speed"),4,getParamValue(greenSelect,blueSelect,operatorSelect,4,0)); break;
    case 5: showValueOnScreen(F("Wet"),5,getParamValue(greenSelect,blueSelect,operatorSelect,5,0)); break;
    case 6: showValueOnScreen(F("Dry"),6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0)); break;
  }
}

void showReverbDisplay(uint8_t op) {
  switch (op) {
    case 0: showMessageOnScreen(0,F("Reverb")); break;
    case 1: showReverbModeOnScreen(1,getParamValue(greenSelect,blueSelect,operatorSelect,1,0)); break;
    case 2: showMessageOnScreen(2,F("Reverb")); break;
    case 3: showValueOnScreen(F("Damp"),3,getParamValue(greenSelect,blueSelect,operatorSelect,3,0)); break;
    case 4: showValueOnScreen(F("Decay"),4,getParamValue(greenSelect,blueSelect,operatorSelect,4,0)); break;
    case 5: showValueOnScreen(F("Wet"),5,getParamValue(greenSelect,blueSelect,operatorSelect,5,0)); break;
    case 6: showValueOnScreen(F("Dry"),6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0)); break;
  }
}

void showChorusDisplay(uint8_t op) {
  switch (op) {
    case 0: showValueOnScreen(F("Phase"),0,getParamValue(greenSelect,blueSelect,operatorSelect,0,0)); break;
    case 1: showChorusModeOnScreen(1,getParamValue(greenSelect,blueSelect,operatorSelect,1,0)); break;
    case 2: showValueOnScreen(F("Feedback"),2,getParamValue(greenSelect,blueSelect,operatorSelect,2,0)); break;
    case 3: showValueOnScreen(F("Depth"),3,getParamValue(greenSelect,blueSelect,operatorSelect,3,0)); break;
    case 4: showValueOnScreen(F("Speed"),4,getParamValue(greenSelect,blueSelect,operatorSelect,4,0)); break;
    case 5: showValueOnScreen(F("Wet"),5,getParamValue(greenSelect,blueSelect,operatorSelect,5,0)); break;
    case 6: showValueOnScreen(F("Dry"),6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0)); break;
  }
}

void showEffectsDisplay(uint8_t op) {
  switch (op) {
    case 0: showEffectsStatusDisplay(op,false); break;
    case 1: showValueOnScreen(F("Bitcrusher"),1,getParamValue(greenSelect,blueSelect,operatorSelect,1,0)); break;
    case 2: showValueOnScreen(F("Decimator"),2,getParamValue(greenSelect,blueSelect,operatorSelect,2,0)); break;
    case 3: showFilterDisplay(op); break;
    case 4: showFilterDisplay(op); break;
    case 5: showEffectsRoutingOnScreen(5,getParamValue(greenSelect,blueSelect,operatorSelect,5,0),0,0); break;
    case 6: showEffectsStatusDisplay(op,true); break;
  }
}

uint8_t getDepth(uint8_t wet, uint8_t dry) {
  if (wet==0) {
    return 0;
  } else {
    uint16_t depth = 255 * wet;
    return depth / (wet + dry);
  }
}

void showEffectsStatusDisplay(uint8_t op, bool first) {
  if (first) {
    //Chorus, Reverb, Phaser
    uint8_t chorus = getDepth(getParamValue(greenSelect,BLUE_RATIO,operatorSelect,5,0),getParamValue(greenSelect,BLUE_RATIO,operatorSelect,6,0));
    uint8_t reverb = getDepth(getParamValue(greenSelect,BLUE_PITCH,operatorSelect,5,0),getParamValue(greenSelect,BLUE_PITCH,operatorSelect,6,0));
    uint8_t phaser = getDepth(getParamValue(greenSelect,BLUE_FEEDBACK,operatorSelect,5,0),getParamValue(greenSelect,BLUE_FEEDBACK,operatorSelect,6,0));
    showEffectsStatusOnScreen(op,F("Chorus"),chorus,F("Reverb"),reverb,F("Phaser"),phaser);
  } else {
    //Delay, AM
    uint8_t delay = getDepth(getParamValue(greenSelect,BLUE_DURATION,operatorSelect,5,0),getParamValue(greenSelect,BLUE_DURATION,operatorSelect,6,0));
    showEffectsStatusOnScreen(op,F("Delay"),delay,F("AM"),getParamValue(greenSelect,BLUE_LEVEL,operatorSelect,5,0),F(""),0);
  }
}

void showFilterDisplay(uint8_t op) {
  showFilterOnScreen(3,getParamValue(greenSelect,BLUE_VOLUME,operatorSelect,4,0),getParamValue(greenSelect,BLUE_VOLUME,operatorSelect,3,0));
  ShowFilterMessageOnScreen(4,operatorSelect==4,operatorSelect==3);
}

void showMasterDisplay(uint8_t op) {
  switch (blueSelect) {
    case 0: showMaster(op); break;
    case 1: showReserved(op); break;
    case 2: showVeloSense(op,0); break;
    case 3: showVeloSense(op,1); break;
    case 4: showMixer(op,0); break;
    case 5: showMixer(op,1); break;
  }
}

//
// LFO submenu
//
void showAMS(uint8_t op) {
  if (op==6) {
    showVolumeOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0));
  } else {
    showValueOnScreen(F("Ampl Depth"),op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0));
  }
}

void showPMS(uint8_t op) {
  if (op==6) {
    showVolumeOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0));
  } else {
    showValueOnScreen(F("Pitch Depth"),op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0));
  }
}

void showKeyTracking(uint8_t op) {
  //TODO: this is not really correct: keytrack is BP and curve, showNoteOnScreen is only BP!
  if (op==6) {
    showVolumeOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0));
  } else {
    showNoteOnScreen(op
      ,getParamValue(greenSelect,BLUE_PITCH,operatorSelect,op,0)
      ,60,false
      ,getParamValue(greenSelect,BLUE_RATIO,operatorSelect,op,0)
      ,getParamValue(greenSelect,BLUE_RATIO,operatorSelect,op,1)
      ,getParamValue(greenSelect,BLUE_FEEDBACK,operatorSelect,op,0)
      ,getParamValue(greenSelect,BLUE_FEEDBACK,operatorSelect,op,1)
    );
  }
}

void showLFO(uint8_t op) {
  switch (op) {
    case 0: displayLFOWave(0,getParamValue(greenSelect,blueSelect,operatorSelect,0,0)); break;
    case 1: showValueOnScreen(F("LFO Speed"),1,getParamValue(greenSelect,blueSelect,operatorSelect,1,0)); break;
    case 2: showLFOSyncOnScreen(2,getParamValue(greenSelect,blueSelect,operatorSelect,2,0)); break;
    case 3: showValueOnScreen(F("LFO Fade"),3,getParamValue(greenSelect,blueSelect,operatorSelect,3,0)); break;
    case 4: showValueOnScreen(F("Pitch Depth"),4,getParamValue(greenSelect,blueSelect,operatorSelect,4,0)); break;
    case 5: showValueOnScreen(F("Ampl Depth"),5,getParamValue(greenSelect,blueSelect,operatorSelect,5,0)); break;
    case 6: showVolumeOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0)); break;
  }
}

//
// Oscillator submenu
//
void showPitchEnvelope(uint8_t op) {
  if (op==6) {
    env_type env;
    env.level[0] = getParamValue(greenSelect,BLUE_LEVEL,op,6,0); //Start level
    env.level[1] = getParamValue(greenSelect,BLUE_LEVEL,op,0,0); //Level at end of attack phase
    env.level[2] = getParamValue(greenSelect,BLUE_LEVEL,op,1,0); //Level at end of decay-1 phase
    env.level[3] = getParamValue(greenSelect,BLUE_LEVEL,op,3,0); //Level at end of decay-2 phase (= sustain level)
    env.level[4] = getParamValue(greenSelect,BLUE_LEVEL,op,4,0); //Level at end of release-1 phase
    env.level[5] = getParamValue(greenSelect,BLUE_LEVEL,op,5,0); //Level at end of release-2 phase (= end level)
    env.rate[0] = getParamValue(greenSelect,BLUE_DURATION,op,6,0); //Delay
    env.rate[1] = getParamValue(greenSelect,BLUE_DURATION,op,0,0); //Rate of attack phase
    env.rate[2] = getParamValue(greenSelect,BLUE_DURATION,op,1,0); //Rate of decay-1 phase
    env.rate[3] = getParamValue(greenSelect,BLUE_DURATION,op,2,0); //Rate of decay-2 phase
    env.rate[4] = getParamValue(greenSelect,BLUE_DURATION,op,4,0); //Rate of releease-1 phase
    env.rate[5] = getParamValue(greenSelect,BLUE_DURATION,op,5,0); //Rate of releease-2 phase

    uint8_t sel = (blueSelect-4)*7+operatorUsed;
    if (sel==13) {
      sel = 14; //Not "rate" but "range" for pitch envelope
    }

    showEnvelopeOnScreen(6,sel,env,true,getParamValue(greenSelect,blueSelect,operatorSelect,operatorUsed,0),blueSelect==BLUE_LEVEL && sel!=14,getParamValue(greenSelect,BLUE_LEVEL,operatorSelect,6,0)); //Last parameter is incorrect!
  } else {
    // Pitch envelope is only displayed in screen 6, so other screens can display the "overview" mode
    showOverview(op);
  }
}

void showPhase(uint8_t op) {
  if (op==6) {
    showVolumeOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0));
  } else {
    showPhaseOnScreen(op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0),getParamValueBit(greenSelect,blueSelect,operatorSelect,op,1,op));
  }
}

void showWave(uint8_t op, uint8_t widx) {
  if (op==6) {
    showVolumeOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0));
  } else {
    displayWave(op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0));
  }
}

void showOSCRatio(uint8_t op) {
  if (op==6) {
    showVolumeOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0));
  } else {
    showOSCRatioOnScreen(op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0),getParamValue(greenSelect,blueSelect,operatorSelect,op,1));
  }
}

//
// Operator submenu
//
void showAmplitudeEnvelope(uint8_t op) {
  if (op==operatorSelect) {
    showOperator(6,operatorSelect);
  }
  if (op<6) {
    env_type env;
    env.level[0] = getParamValue(greenSelect,BLUE_LEVEL,op,6,0); //Start level
    env.level[1] = getParamValue(greenSelect,BLUE_LEVEL,op,0,0); //Level at end of attack phase
    env.level[2] = getParamValue(greenSelect,BLUE_LEVEL,op,1,0); //Level at end of decay-1 phase
    env.level[3] = getParamValue(greenSelect,BLUE_LEVEL,op,3,0); //Level at end of decay-2 phase (= sustain level)
    env.level[4] = getParamValue(greenSelect,BLUE_LEVEL,op,4,0); //Level at end of release-1 phase
    env.level[5] = getParamValue(greenSelect,BLUE_LEVEL,op,5,0); //Level at end of release-2 phase (= end level)
    env.rate[0] = getParamValue(greenSelect,BLUE_DURATION,op,6,0); //Delay
    env.rate[1] = getParamValue(greenSelect,BLUE_DURATION,op,0,0); //Rate of attack phase
    env.rate[2] = getParamValue(greenSelect,BLUE_DURATION,op,1,0); //Rate of decay-1 phase
    env.rate[3] = getParamValue(greenSelect,BLUE_DURATION,op,2,0); //Rate of decay-2 phase
    env.rate[4] = getParamValue(greenSelect,BLUE_DURATION,op,4,0); //Rate of releease-1 phase
    env.rate[5] = getParamValue(greenSelect,BLUE_DURATION,op,5,0); //Rate of releease-2 phase

    showEnvelopeOnScreen(op,(blueSelect-4)*7+operatorUsed,env,(op==operatorSelect),getParamValue(greenSelect,blueSelect,operatorSelect,operatorUsed,0),false,getParamValue(greenSelect,BLUE_LEVEL,operatorSelect,6,0)); //Last parameter is incorrect
  }
}

void showFeedback(uint8_t op) {
  if (op==6) {
    showVolumeOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0));
  } else {
    showFeedbackOnScreen(op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0),getParamValueBit(greenSelect,BLUE_LEDS,0,op,0,op+1));
  }
}

void showRatioPitch(uint8_t op) {
  if (op==6) {
    showVolumeOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0));
  } else {
    showRatioOnScreen(op,bitRead(getParamValue(greenSelect,2,operatorSelect,op,1),op)==1,(blueSelect==2 ? 2 : toggleMode),getParamValue(greenSelect,1,operatorSelect,op,0),getParamValue(greenSelect,1,operatorSelect,op,1),getParamValue(greenSelect,2,operatorSelect,op,0));
  }
}

void showLevel(uint8_t op) {
  if (op==6) {
    showVolumeOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0));
  } else {
    if (displayMode==DISPLAY_OVERVIEW) {
      showOverview(op);
    } else {
      showValueOnScreen(F("Level"),op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0));
    }
  }
}

void showOverview(uint8_t op) {
  env_type env;
  env.level[0] = getParamValue(GREEN_OPS,BLUE_LEVEL,op,6,0); //Start level
  env.level[1] = getParamValue(GREEN_OPS,BLUE_LEVEL,op,0,0); //Level at end of attack phase
  env.level[2] = getParamValue(GREEN_OPS,BLUE_LEVEL,op,1,0); //Level at end of decay-1 phase
  env.level[3] = getParamValue(GREEN_OPS,BLUE_LEVEL,op,3,0); //Level at end of decay-2 phase (= sustain level)
  env.level[4] = getParamValue(GREEN_OPS,BLUE_LEVEL,op,4,0); //Level at end of release-1 phase
  env.level[5] = getParamValue(GREEN_OPS,BLUE_LEVEL,op,5,0); //Level at end of release-2 phase (= end level)
  env.rate[0] = getParamValue(GREEN_OPS,BLUE_DURATION,op,6,0); //Delay
  env.rate[1] = getParamValue(GREEN_OPS,BLUE_DURATION,op,0,0); //Rate of attack phase
  env.rate[2] = getParamValue(GREEN_OPS,BLUE_DURATION,op,1,0); //Rate of decay-1 phase
  env.rate[3] = getParamValue(GREEN_OPS,BLUE_DURATION,op,2,0); //Rate of decay-2 phase
  env.rate[4] = getParamValue(GREEN_OPS,BLUE_DURATION,op,4,0); //Rate of releease-1 phase
  env.rate[5] = getParamValue(GREEN_OPS,BLUE_DURATION,op,5,0); //Rate of releease-2 phase
  showOperatorOverviewOnScreen(op,env,getParamValue(GREEN_OPS,BLUE_VOLUME,operatorSelect,op,0),getParamValue(GREEN_OPS,BLUE_RATIO,operatorSelect,op,0),getParamValue(GREEN_OPS,BLUE_RATIO,operatorSelect,op,1),getParamValueBit(GREEN_OPS,BLUE_LEDS,0,op,0,op+1));
}

//
// Effects submenu
//

//
// Master submenu
//
void showMixer(uint8_t op, uint8_t unit) {
  if (op==6) {
    showVolumeUnitOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0),unit);
  } else {
    showMixerOnScreen(op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0),getParamValue(greenSelect,blueSelect,operatorSelect,op,1),unit);
  }
}

void showVeloSense(uint8_t op, uint8_t unit) {
  if (op==6) {
    showValueOnScreen(F("Velo offset"),op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0));
  } else {
    showValueOnScreen(F("Velo sense"),op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0));
  }
}

void showReserved(uint8_t op) {
  showValueOnScreen(F("Reserved"),op,getParamValue(greenSelect,blueSelect,operatorSelect,op,0));
}

void showMaster(uint8_t op) {
  switch (op) {
    case 0: showPanOnScreen(0,getParamValue(greenSelect,blueSelect,operatorSelect,0,0)); break;
    case 1: showNoteOnScreen(1,getParamValue(greenSelect,blueSelect,operatorSelect,1,0),24,true,0,0,0,0); break;
    case 2: showMonoPolyOnScreen(2,getParamValue(greenSelect,blueSelect,operatorSelect,2,0)); break;
    case 3: showValueOnScreen(F("Porta time"),3,getParamValue(greenSelect,blueSelect,operatorSelect,3,0)); break;
    case 4: showPortaModeOnScreen(4,getParamValue(greenSelect,blueSelect,operatorSelect,4,0)); break;
    case 5: showTuningOnScreen(5,getParamValue(greenSelect,blueSelect,operatorSelect,5,0)); break;
    case 6: showOutputGainOnScreen(6,getParamValue(greenSelect,blueSelect,operatorSelect,6,0),getParamValue(greenSelect,blueSelect,operatorSelect,6,1)); break;
  }
}
