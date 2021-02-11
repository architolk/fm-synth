# Menu-items

So, this is a synth without a menu? Euh... We do have some kind of menu, but there's no "diving". This page describes all the menu's available.

We have the "green" menu, which is actually split into two parts (synth A & synth B). This is organized as:

| Value | Operation |
|-------|-----------|
| 0 | LFO of synth A |
| 1 | Oscillator of synth A |
| 2 | Operators of synth A |
| 3 | Effects of synth A |
| 4 | Master |
| 5 | Effects of synth B |
| 6 | Operators of synth B |
| 7 | Oscillator of synth B |
| 8 | LFO of synth B |

The "blue" menu consists of 6 possible values and depends on the value of the "green" menu.

# Programming

A "mapping" table maps the configuration of the green menu (0-8), blue menu (0-6) and the encoder that is used (0-6) to a particular parameter. This parameter value is used for the screen. Values above 1000 have a special meaning:
- 1000+: the value minus 1000 is the index to another array containing two parameters that the push button switches between
- 2000+: the value minus 2000 is the index to another array containing two parameters. The first is the parameter of the dial, the second is the parameter for the push button, true/false for a particular bit (corresponding with the operator)
- 3000+: the selected operator index should be added to the value minus 3000, the push button selects the chosen operator

In the mapping tables below "51/63" means toggle between these two parameters and "27/14" means parameter 27 for dial and 14 for push button and "181+" means paramter 181 + operator index (0-5). The actual values in the matrix will for example have values 1001 and 2008 and 3181, corresponding to index 1 and 8 of the special array, and parameters 181 to 186, depending on the chosen operator.

An array blueMenu[9] is used to define the value of the blue button whenever a green button is pressed, so you return to the same state after pressing a green button. BUT: the values of synth A en synth B are mirrored, so you can swiftly switch between synth engines.

An array paramvalues[2][800] is used to capture the values of a specific parameter, per synth engine.
A variable encoderSelected is used to capture which encoder is selected (might change this into a bit array!)

Any combination of the green menu and the blue menu will change all screens, according to the table below:

| Green | Blue | Screen | Screeen type |
|-------|------|--------|--------------|
| 0+8 | 0 | LFO | Multiple |
| 0+8 | 1 | Key tracking | Curves + Depth + Break point note |
| 0+8 | 2 | Key tracking | Curves + Depth + Break point note |
| 0+8 | 3 | Key tracking | Curves + Depth + Break point note |
| 0+8 | 4 | LFO-PMS | Level |
| 0+8 | 5 | LFO-AMS | Level |
| 1+7 | 0 | Wave 1 | Wave |
| 1+7 | 1 | OSC-Ratio | Frequency ratio |
| 1+7 | 2 | Wave 2 | Wave |
| 1+7 | 3 | Oscillator phase | Phase + Sync |
| 1+7 | 4 | Pitch envelope | Envelope |
| 1+7 | 5 | Pitch envelope | Envelope |
| 2+6 | 0 | Level | Level |
| 2+6 | 1 | Ratio | Course + Fine Ratio |
| 2+6 | 2 | Pitch | Pitch |
| 2+6 | 3 | Feedback | Level |
| 2+6 | 4 | Amplitude envelope | Envelope |
| 2+6 | 5 | Amplitude envelope | Envelope |
| 3+5 | 0 | Effects | Multiple |
| 3+5 | 1 | Effects | Multiple |
| 3+5 | 2 | Effects | Multiple |
| 3+5 | 3 | Effects | Multiple |
| 3+5 | 4 | Effects | Multiple |
| 3+5 | 5 | Effects | Multiple |
| 4 | 0 | Master | Multiple |
| 4 | 1 | Reserved | Non |
| 4 | 2 | Velo sense | Level |
| 4 | 3 | Velo sense | Level |
| 4 | 4 | Mixer | Stereo Level |
| 4 | 5 | Mixer | Stereo Level |

# Green Menu

## LFO (green 0 & 8)

In LFO mode, the displays will show the parameter for the particular encoder

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | Wave | Speed | Sync | Fade | Pitch depth | Amp depth | Volume |
| 1 | R Depth/Curve | R Depth/Curve | R Depth/Curve | R Depth/Curve | R Depth/Curve | R Depth/Curve | Volume |
| 2 | Key BP | Key BP | Key BP | Key BP | Key BP | Key BP | Volume |
| 3 | L Depth/Curve | L Depth/Curve | L Depth/Curve | L Depth/Curve | L Depth/Curve | L Depth/Curve | Volume |
| 4 | PMS | PMS | PMS | PMS | PMS | PMS | Volume |
| 5 | AMS | AMS | AMS | AMS | AMS | AMS | Volume |

Mapping of parameters:

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | 153 | 151 | 152 | 154 | 149 | 150 | 180 |
| 1 | 57 | 58 | 59 | 60 | 61 | 62 | 180 |
| 2 | 45 | 46 | 47 | 48 | 49 | 50 | 180 |
| 3 | 51/63 | 52/64 | 53/65 | 54/66 | 55/67 | 56/68 | 180 |
| 4 | 222 | 223 | 224 | 225 | 226 | 227 | 180 |
| 5 | 159 | 160 | 161 | 162 | 163 | 164 | 180 |

Depth and Curve are selected by toggling using the push button

All zeven screens display the value for the current selection
For the keyboard tracking selection (values 1,2,3) the same screen is shown, with all parameters in one display

- AMS means Amplitude Modulation Sensitivity of the LFO to that particular operator
- PMS means Pitch Modulation Sensitivity of the LFO to that particular operator
- Volume simply means output volume
- Wave sets the LFO Wave: 0=Triangle, 1=Square, 2=Saw up, 3=Saw down, 4=Sine, 5=Random
- Speed sets the LFO speed
- Sync defines the LFO behavior: 0=Single & free running, 1=Single & key sync, 2=Multi & free running, 3=Multi & key sync
- Fade sets the time for the LFO effect to ramp up to the maximum
- Pitch depth sets the fixed LFO effect depth applied to pitch
- Amp depth set the fixed LFO effect depth applied to amplitude
- Key BP sets the keyboard breakpoint for tracking, for that particular operator
- L Depth adjusts the depth of the scaling left of the breakpoint
- R Depth adjusts the depth of the scaling right of the breakpoint
- Curve set the curve: 0=exp-, 1=lin-, 2=lin+, 3=exp+

## Oscillator (1 & 7)

In Oscillator mode, the displays will show the parameter for the particular encoder

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Volume |
| 1 | Ratio | Ratio | Ratio | Ratio | Ratio | Ratio |  |
| 2 | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Wave 1 |  |
| 3 | Phase+sync | Phase+sync | Phase+sync | Phase+sync | Phase+sync | Phase+sync |  |
| 4 | Attack | Decay-1 | Decay-2 |  | Release-1 | Release-2 | Delay |
| 5 | Attack | Decay-1 | Decay-2 | Sustain | Release-1 | Release-2 | Delay | Rate |

Mapping of parameters:

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | 236 | 237 | 238 | 239 | 240 | 241 | 180 |
| 1 | 280 | 281 | 282 | 283 | 284 | 285 | 0 |
| 2 | 268 | 269 | 270 | 271 | 272 | 273 | 0 |
| 3 | 286 | 287 | 288 | 289 | 290 | 291 | 0 |
| 4 | 134 | 135 | 136 | 0 | 137 | 208 | 206 |
| 5 | 205 | 130 | 131 | 132 | 133 | 207 | 146 |

All zeven screens display the value for the current selection
For the pitch envelope (values 4,5) the same screen is shown, displaying the envelope graph

- Attach, Decay-1, Decay-2, Sustain, Release-1, Release-2, Delay are parameters for the envelope
- Range sets the range of the pitch envelope, in octaves
- Phase sets the phase for the oscillator per operator (0=0, 1=90, 2=180, 3=270)
- Sync sets the synchronization of the oscillator per operator (free running or sync to note-on)
- Rate sets how the EG times change with the generating MIDI notes
- Velo sets how much the range changes with MIDI velocity
- Wave 1 sets the wave shape for oscillator 1 of the particular operator (range 0-7)
- Ratio sets the frequency ratio between oscillator 1 and 2 of the particular operator
- Wave 2 sets the wave shape for oscillator 2 of the particular operator (range 0-7)

(Range, Rate en Velo zijn nog niet toegekend - ff kijken hoe dit werkt...)

Phase and Sync seems linked: no sync, no phase? So probably we can combine these values (no sync, 0 degree sync, 90 degree sync, 180 degree sync, 270 degree sync - or are free running oscillators still in sync with each other???)

"Loop" is for the pitch operator not defined, but EG RESTART is defined. Not sure what this means....

## Operators (2 & 6)

In Operators mode, the displays will show the parameter for the particular encoder

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | Level | Level | Level | Level | Level | Level | Volume |
| 1 | Ratio/R.Fine | Ratio/R.Fine | Ratio/R.Fine | Ratio/R.Fine | Ratio/R.Fine | Ratio/R.Fine |  |
| 2 | Fine (Mode) | Fine (Mode) | Fine (Mode) | Fine (Mode) | Fine (Mode) | Fine (Mode) |  |
| 3 | Feedback | Feedback | Feedback | Feedback | Feedback | Feedback |  |
| 4 | Attack | Decay-1 | Decay-2 |  | Release-1 | Release-2 | Delay |
| 5 | Attack | Decay-2 | Decay-2 | Sustain | Release-1 | Release-2 | Rate |

Mapping of parameters:

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | 33 | 34 | 35 | 36 | 37 | 38 | 180 |
| 1 | 15/21 | 16/22 | 17/23 | 18/24 | 19/25 | 20/26 | 0 |
| 2 | 27 (14) | 28 (14) | 29 (14) | 30 (14) | 31 (14) | 32 (14) | 0 |
| 3 | 7 | 8 | 9 | 10 | 11 | 12 | 0 |
| 4 | 103+ | 110+ | 117+ | 0 | 124+ | 199+ | 187+ |
| 5 | 181+ | 75+ | 82+ | 89+ | 96+ | 193+ | 140+ |

- Level is the level of the particular operator
- Volume is the output volume of the synth
- Ratio is the coarse ratio of the operator
- R.Fine is the fine ratio of the operator
- Fine is the percentage pitch of the operator
- Mode is a toggle between fixed pitch and MIDI-pitch
- Feedback is the level of feedback for the particular operator to itself
- Attach, Decay-1, Decay-2, Sustain, Release-1, Release-2, Delay are parameters for the envelope
- Rate sets how the EG times change with the generating MIDI notes

Ratio/R.Fine are toggled using the push button
Mode is toggle using the push button

In envelope mode, the push buttons selected the specific operator. So all operators are displayed, but only one envelope will change.
(maybe we introduce something to select multiple operators, if we want to change multiple envelopes the same way???)

## Effects (3 & 5)

In effects mode, the displays will show the parameters for a particular effect. We suspect that we can have all effects displayed at the same time, needs to be investigated!

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 |   | *Decimator* Depth | *Filter* Lo pass | *Filter* Hi pass | *Bitcrusher* Depth | EFX Routing | Volume |
| 1 | *Chorus/Flanger* Wet | *Chorus/Flanger* Speed | *Chorus/Flanger* Depth | *Chorus/Flanger* Mode | *Chorus/Flanger* Feedback | *Chorus/Flanger* LR Phase | *Chorus/Flanger* Dry |
| 2 | *Reverb* Wet | *Reverb* Decay | *Reverb* Mode | *Reverb* Damp |  |  | *Reverb* Dry |
| 3 | *Phaser* Wet | *Phaser* Speed | *Phaser* Depth | *Phaser* Offset/Stages | *Phaser* Feedback | *Phaser* LR Phase | *Phaser* Dry |
| 4 | *Delay* Wet | *Delay* Time/Tempo | *Delay* Lo pass | *Delay* Hi pass | *Delay* Feedback | *Delay* Multiplier/Devider | *Delay Dry |
| 5 |  | *AM* Speed | *AM* Depth | *AM* Range |  | *AM* LR Phase |  |

Chorus/Fanger is one effect, this is selected by the Mode parameter

Mapping of parameters:

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | 0 | 370 | 320 | 321 | 380 | 410 | 180 |
| 1 | 361 | 363 | 364 | 362 | 365 | 366 | 360 |
| 2 | 391 | 393 | 392 | 394 | 0 | 0 | 390 |
| 3 | 311 | 314 | 313 | 316/317 | 315 | 318 | 310 |
| 4 | 301 | 303/307 | 305 | 306 | 304 | 308/309 | 300 |
| 5 | 0 | 330 | 332 | 331 | 0 | 333 | 0 |

## Master (4)

In master mode, the displays will show the master parameters

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | Pan | Transpose | Mono-Poly | Porta time | Porta mode | Tuning | Output/Gain |
| 1 |   |   |   |   |   |   |   |
| 2 | Velo sense U2 | Velo sense U2 | Velo sense U2 | Velo sense U2 | Velo sense U2 | Velo sense U2 | Velo offset U2 |
| 3 | Velo sense U1 | Velo sense U1 | Velo sense U1 | Velo sense U1 | Velo sense U1 | Velo sense U1 | Velo offset U1 |
| 4 | Vol U2-L/R | Vol U2-L/R | Vol U2-L/R | Vol U2-L/R | Vol U2-L/R | Vol U2-L/R | Vol U2 |
| 5 | Vol U1-L/R | Vol U1-L/R | Vol U1-L/R | Vol U1-L/R | Vol U1-L/R | Vol U1-L/R | Vol U1 |

Mapping of parameters:

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | 221 | 174 | 228 | 230 | 229 | 251 | 411/412 |
| 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| 2 | 39 | 40 | 41 | 42 | 43 | 44 | 242 |
| 3 | 39 | 40 | 41 | 42 | 43 | 44 | 242 |
| 4 | 256/257 | 258/259 | 260/261 | 262/263 | 264/265 | 266/267 | 180 |
| 5 | 256/257 | 258/259 | 260/261 | 262/263 | 264/265 | 266/267 | 180 |

Options 2-5 target a specific unit, so the parameter values are the same for both units, but the specified unit should be selected.
