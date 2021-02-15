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

  paramValue[unit][0] = 0; //Parameter 0 doesn't exist, set to zero
  if (HWSERIAL.available() == 512) {
    for (uint16_t param=1; param<513; param++) {
      paramValue[unit][param] = HWSERIAL.read();
    }
    return true;
  } else {
    //Something went wrong: result of dump operation should be 512 bytes response
    return false;
  }
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
