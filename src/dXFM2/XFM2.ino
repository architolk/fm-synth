/*
*  Module for the interaction with the XFM2
*
*  this module is about interaction with the XFM2
*  via the serial communication bus
*
*/

//Sets the unit that is active
//All communication that follows will be for this unit
//A call to this function is only necessary when you switch between units
//XFM2 expects "1" or "2", we use 0 and 1 for units, so 0=>"1" and 1=>"2"
bool xfm2SetUnit( uint8_t unit ) {
    // Default to unit 1
    HWSERIAL.write( unit == 1 ? '2' : '1' );
    delay(50); //Give the XFM2 time to respond
    if (HWSERIAL.available() == 1) {
      uint8_t result = HWSERIAL.read();
      return true;
    } else {
      //Something went wrong: result of setting the unit should be 0 for unit 1 and 1 for unit 2
      return false;
    }
}

//Sets the value for a particular parameter, for the active unit
void xfm2SetParameter( uint16_t param, uint8_t value ) {
    HWSERIAL.write( 's' ); // 's' = Set Parameter

    if( param > 255 ) {
        // Parameters above 255 have a two-byte format: b1 = 255, b2 = x-256
        HWSERIAL.write( 255 );
        HWSERIAL.write( param - 256  );
        HWSERIAL.write( value );
    } else {
        HWSERIAL.write( param );
        HWSERIAL.write( value );
    }

    //Set parameter doesn't return anything, so no serial write
}

//Retrieves the active program and stores it in the param storage
//This function DOESN'T set the active unit for the XFM2
//So make sure that the active unit is actually corresponding to requested unit
bool xfm2GetActiveProgram(uint8_t unit) {
  HWSERIAL.write('d'); // 'd' = Displays all parameter values for active program

  char serialBuffer[512];
  int count = HWSERIAL.readBytes(serialBuffer,512);

  if (count==512) {
    for (uint16_t param=0; param<512; param++) {
      paramValue[0][param] = serialBuffer[param];
    }
    return true;
  } else {
    return false;
  }
}

//Pushes the param storage to the active program on the XFM2
//Normally, the param storage is in sync with the active program
//this function is only needed when you change the param storage in bulk
//(at this moment only needed for the default DX7 patches)
//(might be needed if we add some serial interface directly from Teensy)
bool xfm2PushActiveProgram(uint8_t unit) {
  //No push-operation is available on the XFM2, so we need to do this parameter-for-parameter
  for (uint16_t param=0; param<512; param++) {
    xfm2SetParameter(param,paramValue[unit][param]);
    delay(2); //Give the XFM2 some time (one second total delay)
  }
  return true; //No way of telling something went wrong :-(
}

uint8_t initXFM2() {
  if (xfm2SetUnit(0)) {
    if (xfm2GetActiveProgram(0)) {
      return NO_ERROR;
    } else {
      return ERR_DUMP;
    }
  } else {
    return ERR_UNIT;
  }
}

//Loads a program from EEPROM
bool xfm2LoadPatch( uint8_t patch ) {
    HWSERIAL.write('r'); // 'd' = Displays all parameter values for active program
    HWSERIAL.write(patch);
    delay(100); //Give the XFM2 time to respond
    if (HWSERIAL.available() == 1) {
      uint8_t result = HWSERIAL.read();
      return true;
    } else {
      //Something went wrong: result of setting the unit should be 0
      return false;
    }
}

//Initialize active program
//Not actually sure what this does: maybe set the active program to some default values???
bool xfm2InitPatch() {
    HWSERIAL.write('i'); // 'i' = Initialize active program
    delay(100); //Give the XFM2 time to respond
    if (HWSERIAL.available() == 1) {
      uint8_t result = HWSERIAL.read();
      return true;
    } else {
      //Something went wrong: result of setting the unit should be 0
      return false;
    }
}
