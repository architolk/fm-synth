/*
*  Module for the interaction with the XFM2
*
*  this module is about interaction with the XFM2
*  via the serial communication bus
*
*/
#define NO_ERROR 0
#define ERR_UNIT 1
#define ERR_DUMP 2

//Sets the unit that is active
//All communication that follows will be for this unit
//A call to this function is only necessary when you switch between units
bool xfm2SetUnit( int unit ) {
    // Default to unit 1
    HWSERIAL.write( unit == 2 ? '2' : '1' );
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
bool xfm2GetActiveProgram() {
  HWSERIAL.write('d'); // 'd' = Displays all parameter values for active program

  if (HWSERIAL.available() == 512) {
    for (uint16_t param=0; param++; param<512) {
      paramValue[0][param] = HWSERIAL.read();
    }
    return true;
  } else {
    //Something went wrong: result of dump operation should be 512 bytes response
    return false;
  }
}

uint8_t initXFM2() {
  if (xfm2SetUnit(1)) {
    if (xfm2GetActiveProgram()) {
      return NO_ERROR;
    } else {
      return ERR_DUMP;
    }
  } else {
    return ERR_UNIT;
  }
}
