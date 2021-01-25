/* Simple test for interupts & debouncing of rotary encoder
*
* Connections:
* GND to middle pin of the encoder and one of the switch pins
* Pin 2 from teensy to left pin of rotary encoder
* Pin 3 from teensy to right pin of rotary encoder
* Pin 4 from teensy to the remaining switch pin
*/

// Variables without interupt
/*
int n = LOW;
int encoderPos = 0;
int encoder0PinALast = HIGH;
*/

//Variables with interupt
volatile unsigned int encoderPos = 0;  // a counter for the dial
unsigned int lastReportedPos = 1;   // change management
static boolean rotating = false;    // debounce management

// interrupt service routine vars
boolean A_set = false;
boolean B_set = false;

void setup() {
  // put your setup code here, to run once:
  pinMode (2, INPUT_PULLUP);
  pinMode (3, INPUT_PULLUP);
  pinMode (4, INPUT_PULLUP);

  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(2, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(3, doEncoderB, CHANGE);

  Serial.begin(9600);  // output
  Serial.println("Starting");
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(digitalRead(4));

  // Encoder stuff (without interupts)
  /*
  n = digitalRead(2);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(3) == LOW) {
      encoderPos--;
    } else {
      encoderPos++;
    }
    Serial.println(encoderPos);
    delay(50);
  }
  encoder0PinALast = n;
  */

  //Encoder stuff (with interupts)
  rotating = true;  // reset the debouncer
  if (lastReportedPos != encoderPos) {
    Serial.println(encoderPos);
    lastReportedPos = encoderPos;
  }
  if (digitalRead(4) == LOW) {
    encoderPos = 5;
  }
}

// Interrupt on A changing state
void doEncoderA() {
  // debounce
  if ( rotating ) delay (1);  // wait a little until the bouncing is done

  // Test transition, did things really change?
  if ( digitalRead(2) != A_set ) { // debounce once more
    A_set = !A_set;

    // adjust counter + if A leads B
    if ( A_set && !B_set )
      encoderPos += 1;

    rotating = false;  // no more debouncing until loop() hits again
  }
}

// Interrupt on B changing state, same as A above
void doEncoderB() {
  if ( rotating ) delay (1);
  if ( digitalRead(3) != B_set ) {
    B_set = !B_set;
    //  adjust counter - 1 if B leads A
    if ( B_set && !A_set )
      encoderPos -= 1;

    rotating = false;
  }
}
