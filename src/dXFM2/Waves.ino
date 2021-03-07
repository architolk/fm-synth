/*
*  Module for the waves
*
*  this module is about storing the wavesforms that can be displayed
*
*/

//Data is structured as a sample value range -127 to 127

//Wave forms for the synth, created with the WCreate utility
//0 = Sine wave: "(x=1)"
//1 = Triangle wave with one odd partical: "(x=1)*0.8-(x=3)/9" (0.8 for better display, a 1.0 first harmonic would be more correct)
//2 = Triangle wave with two odd particals: "(x=1)-(x=3)/9+(x=5)/25"
//3 = Triangle wave without the 3th harmonic, upto the 13th odd harmonic: "(x=1)+(x=5)/25-(x=7)/49+(x=9)/81-(x=11)/121+(x=13)/169"
//4 = Wave with odd particals: "(x=1)+(x=3)/9-(x=5)/25+(x=7)/49-(x=9)/81+(x=11)/121"
//5 = Wave with odd particals: "(x=1)-(x=3)/9-(x=5)/25+(x=7)/49+(x=9)/81-(x=11)/121"
//6 = First and Third partical, in 3/4 - 1/4 ratio: "(x=1)*0.75-(x=3)*0.25"
//7 = Square wave with odd particals from 1 to 17: "(x=1)+(x=3)/3+(x=5)/5+(x=7)/7+(x=9)/9+(x=11)/11+(x=13)/13+(x=15)/15+(x=17)/17"
//Other waves, for LFO:
//8 = Pure triangle
//9 = Pure square
//10 = Pure saw up
//11 = Pure saw down
//12 = Random
const int8_t WAVES[13][122] PROGMEM = {
  {0,12,13,25,26,38,39,51,51,63,63,74,74,84,85,94,94,102,103,110,110,116,116,121,121,124,125,127,127,127,127,127,125,127,122,125,117,122,111,117,104,111,96,104,87,95,76,86,65,76,54,65,41,53,28,40,15,28,2,14,-10,1,-24,-11,-37,-24,-49,-37,-61,-50,-73,-62,-83,-73,-93,-84,-101,-93,-109,-102,-115,-109,-120,-116,-124,-121,-126,-124,-127,-127,-127,-127,-127,-125,-125,-122,-122,-118,-117,-112,-112,-105,-105,-97,-96,-88,-87,-78,-77,-67,-66,-55,-54,-43,-42,-30,-29,-17,-16,-3,-3,0},
  {0,6,6,13,14,21,22,30,30,39,40,50,50,61,62,73,73,85,85,96,96,106,107,115,115,121,122,126,126,127,126,127,123,126,117,122,108,116,98,108,87,98,76,87,64,75,52,63,42,52,32,41,23,31,15,22,8,15,1,7,-5,0,-12,-6,-20,-13,-29,-21,-38,-29,-49,-39,-60,-49,-71,-60,-83,-72,-94,-84,-105,-95,-114,-105,-121,-114,-125,-121,-127,-126,-127,-127,-127,-123,-123,-117,-117,-109,-109,-100,-99,-89,-88,-77,-76,-65,-64,-54,-53,-43,-42,-33,-32,-24,-23,-16,-15,-8,-8,-2,-1,0},
  {0,7,8,16,17,25,26,35,36,45,45,54,54,62,62,70,70,78,79,87,88,98,98,108,109,118,118,125,125,127,126,127,120,125,111,119,100,110,90,99,80,89,72,80,64,71,56,63,47,55,37,46,28,37,18,27,9,18,1,9,-6,0,-15,-7,-24,-16,-34,-25,-43,-34,-53,-44,-61,-53,-69,-61,-77,-69,-86,-78,-96,-87,-107,-97,-117,-108,-124,-117,-127,-124,-127,-126,-126,-121,-120,-112,-111,-101,-101,-91,-90,-81,-81,-73,-72,-65,-64,-57,-56,-48,-47,-38,-38,-29,-28,-19,-19,-10,-10,-2,-1,0},
  {0,13,13,26,27,38,39,50,50,61,61,70,70,77,77,84,84,90,91,96,97,101,101,107,107,115,115,123,123,127,125,127,117,124,108,116,102,108,97,102,92,97,85,92,79,85,71,78,63,71,52,62,41,52,29,40,16,28,2,15,-11,1,-24,-12,-37,-25,-48,-37,-59,-49,-69,-60,-76,-69,-83,-77,-90,-83,-96,-90,-101,-96,-106,-101,-114,-106,-122,-114,-127,-123,-127,-125,-125,-118,-117,-109,-109,-103,-103,-98,-98,-93,-92,-86,-86,-79,-79,-72,-72,-64,-63,-54,-53,-42,-41,-30,-29,-17,-17,-4,-3,0},
  {0,7,7,15,15,23,24,31,32,41,41,52,53,67,68,83,84,98,99,109,110,116,116,120,120,123,123,126,126,127,127,127,124,126,120,124,117,120,111,117,101,111,87,101,71,86,55,70,43,55,33,42,25,33,17,24,9,16,1,8,-6,0,-14,-6,-22,-14,-30,-23,-39,-31,-51,-40,-65,-51,-81,-66,-97,-82,-108,-98,-115,-109,-119,-115,-123,-119,-126,-123,-127,-126,-127,-127,-127,-124,-124,-121,-121,-117,-117,-112,-112,-103,-102,-89,-88,-73,-72,-57,-56,-44,-44,-34,-34,-26,-25,-18,-17,-10,-9,-2,-1,0},
  {0,16,17,33,34,49,50,65,65,79,80,93,94,104,104,112,113,119,119,124,125,127,126,127,121,126,114,120,111,114,111,113,113,119,119,125,125,127,125,127,120,125,114,120,106,114,96,106,83,95,68,82,53,67,37,52,20,36,3,19,-14,2,-31,-15,-47,-32,-63,-48,-78,-64,-91,-79,-103,-92,-111,-103,-118,-112,-124,-119,-127,-124,-127,-127,-126,-121,-121,-115,-114,-111,-112,-111,-118,-113,-125,-119,-127,-125,-127,-126,-126,-121,-121,-115,-114,-107,-107,-97,-96,-84,-84,-70,-69,-55,-54,-39,-38,-22,-21,-5,-4,-1},
  {0,0,0,1,1,3,3,8,8,15,15,25,25,37,37,51,52,66,67,81,82,96,96,108,109,118,119,125,125,127,126,127,120,126,111,120,99,110,85,98,69,84,54,69,40,53,27,39,17,27,9,16,4,9,1,4,0,1,0,0,0,0,0,0,-3,0,-7,-3,-14,-7,-23,-14,-35,-24,-49,-36,-64,-50,-79,-65,-94,-80,-107,-95,-117,-108,-124,-118,-127,-125,-127,-126,-126,-121,-121,-112,-112,-100,-100,-86,-86,-71,-70,-56,-55,-41,-41,-29,-28,-18,-17,-10,-10,-4,-4,-1,-1,0,0,0,0,0},
  {0,102,106,127,101,124,97,103,104,115,107,116,102,107,103,111,110,113,104,110,104,108,109,112,105,111,104,106,106,112,108,112,104,107,105,111,110,112,104,110,104,108,109,113,104,112,102,105,105,115,107,116,97,106,98,120,116,127,22,113,-93,15,-127,-98,-126,-103,-102,-97,-115,-102,-116,-109,-108,-102,-111,-102,-113,-111,-111,-104,-107,-104,-112,-108,-112,-106,-106,-104,-111,-106,-112,-108,-108,-104,-110,-104,-112,-110,-111,-104,-107,-104,-113,-108,-113,-105,-105,-102,-115,-104,-116,-109,-108,-97,-117,-97,-127,-118,-119,-37,-30,-7},
  {0,4,8,13,17,21,25,30,34,38,42,47,51,55,59,63,68,72,76,80,85,89,93,97,102,106,110,114,118,123,127,123,119,115,111,106,102,98,94,90,86,81,77,73,69,65,61,56,52,48,44,40,36,31,27,23,19,15,11,6,2,-2,-6,-10,-14,-19,-23,-27,-31,-35,-39,-44,-48,-52,-56,-60,-64,-69,-73,-77,-81,-85,-89,-94,-98,-102,-106,-110,-114,-119,-123,-127,-123,-118,-114,-110,-106,-102,-97,-93,-89,-85,-80,-76,-72,-68,-63,-59,-55,-51,-47,-42,-38,-34,-30,-25,-21,-17,-13,-8,-4,0},
  {0,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,0},
  {0,-2,-4,-6,-8,-11,-13,-15,-17,-19,-21,-23,-25,-27,-30,-32,-34,-36,-38,-40,-42,-44,-47,-49,-51,-53,-55,-57,-59,-61,-63,-66,-68,-70,-72,-74,-76,-78,-80,-82,-85,-87,-89,-91,-93,-95,-97,-99,-102,-104,-106,-108,-110,-112,-114,-116,-118,-121,-123,-125,-127,127,125,123,121,118,116,114,112,110,108,106,104,102,99,97,95,93,91,89,87,85,82,80,78,76,74,72,70,68,66,63,61,59,57,55,53,51,49,47,44,42,40,38,36,34,32,30,27,25,23,21,19,17,15,13,11,8,6,4,2,0},
  {0,2,4,6,8,11,13,15,17,19,21,23,25,27,30,32,34,36,38,40,42,44,47,49,51,53,55,57,59,61,63,66,68,70,72,74,76,78,80,82,85,87,89,91,93,95,97,99,102,104,106,108,110,112,114,116,118,121,123,125,127,-127,-125,-123,-121,-118,-116,-114,-112,-110,-108,-106,-104,-102,-99,-97,-95,-93,-91,-89,-87,-85,-82,-80,-78,-76,-74,-72,-70,-68,-66,-63,-61,-59,-57,-55,-53,-51,-49,-47,-44,-42,-40,-38,-36,-34,-32,-30,-27,-25,-23,-21,-19,-17,-15,-13,-11,-8,-6,-4,-2,0},
  {0,120,93,127,44,88,45,90,82,103,-21,78,-55,-27,-45,20,23,37,-23,25,-33,-25,-26,-15,-43,-17,-55,-44,-53,-33,-31,-19,-18,-1,0,18,-7,18,-31,-10,-28,26,31,73,33,72,15,30,24,73,29,76,-94,22,-116,-92,-87,6,9,24,-24,6,-21,57,63,116,15,113,-75,7,-76,-40,-36,-15,-65,-20,-73,-52,-48,17,20,31,-14,19,-18,-8,-6,15,16,26,27,48,49,55,23,50,15,21,21,33,-9,31,-37,-13,-33,27,31,55,-49,44,-103,-55,-101,-54,-66,-44,-127,-70,-127,-48,-39,-9}
};

//LFO Mapping:
const uint8_t LFOMAP[6] = {8,9,10,11,0,12};

void displayWave(uint8_t screen,uint8_t wave) {
  showWaveOnScreen(WAVES[wave],screen);
}

void displayLFOWave(uint8_t screen,uint8_t wave) {
  showWaveOnScreen(WAVES[LFOMAP[wave]],screen);
}

void displayLRPhase(uint8_t screen, uint8_t lrphase) {
  uint16_t phasediv = lrphase*30;
  phasediv = phasediv/255;
  uint8_t x = 30-phasediv/2;
  drawWave(WAVES[0],x,30,28);
  drawWave(WAVES[0],x+phasediv,30,28);

}
