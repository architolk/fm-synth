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

A "mapping" table maps the configuration of the green menu (0-8), blue menu (0-6) and the encoder that is used (0-6) to a particular parameter. This parametervalue is used for the screen.

An array blueMenu[9] is used to define the value of the blue button whenever a green button is pressed, so you return to the same state after pressing a green button. BUT: the values of synth A en synth B are mirrored, so you can swiftly switch between synth engines.

Any combination of the green menu and the blue menu will change all screens, according to the table below:

| Green | Blue | Screen |
|-------|------|--------|
| 0 | 0 | LFO-AMS |
| 0 | 1 | LFO-PMS |
| 0 | 2 | Key tracking |
| 0 | 3 | Key tracking |
| 0 | 4 | Key tracking |
| 0 | 5 | LFO |
| 1 | 0 | Pitch envelope |
| 1 | 1 | Pitch envelope |
| 1 | 2 | Oscillator phase |
| 1 | 3 | Wave 2 |
| 1 | 4 | OSC-Ratio |
| 1 | 5 | Wave 1 |

# Green Menu

## LFO (green 0 & 8)

In LFO mode, the displays will show the parameter for the particular encoder

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | AMS | AMS | AMS | AMS | AMS | AMS | Volume |
| 1 | PMS | PMS | PMS | PMS | PMS | PMS | Volume |
| 2 | L Depth (Curve) | L Depth (Curve) | L Depth (Curve) | L Depth (Curve) | L Depth (Curve) | L Depth (Curve) | Volume |
| 3 | Key BP | Key BP | Key BP | Key BP | Key BP | Key BP | Volume |
| 4 | R Depth (Curve) | R Depth (Curve) | R Depth (Curve) | R Depth (Curve) | R Depth (Curve) | R Depth (Curve) | Volume |
| 5 | Wave | Speed | Sync | Fade | Pitch depth | Amp depth | Volume |

Mapping of parameters:

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | 159 | 160 | 161 | 162 | 163 | 164 | 180 |
| 1 | 222 | 223 | 224 | 225 | 226 | 227 | 180 |
| 2 | 51 | 52 | 53 | 54 | 55 | 56 | 180 |
| 3 | 45 | 46 | 47 | 48 | 49 | 50 | 180 |
| 4 | 57 | 58 | 59 | 60 | 61 | 62 | 180 |
| 5 | 153 | 151 | 152 | 154 | 149 | 150 | 180 |

(need something special to map the curve... not in this mapping table!)

All zeven screens display the value for the current selection
For the keyboard tracking selection (values 2,3,4) the same screen is shown, with all parameters in one display

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
| 0 | Attack | Decay-1 | Decay-2 | Sustain | Release-1 | Release-2 | Delay | Rate |
| 1 | Attack (Loop) | Decay-1 (Loop) | Decay-2 (Loop) | (Loop)| Release-1 (Loop) | Release-2 (Loop) | Delay |
| 2 | Phase (sync) | Phase (sync) | Phase (sync) | Phase (sync) | Phase (sync) | Phase (sync) |  |
| 3 | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Wave 1 |  |
| 4 | Ratio | Ratio | Ratio | Ratio | Ratio | Ratio |  |
| 5 | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Volume |

Mapping of parameters:

| Value | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) | 6 (Out) |
|-------|---------|---------|---------|---------|---------|---------|---------|
| 0 | 205 | 130 | 131 | 132 | 133 | 207 | 146 |
| 1 | 134 | 135 | 136 | 0 | 137 | 208 | 206 |
| 2 | 286 | 287 | 288 | 289 | 290 | 291 | 0 |
| 3 | 268 | 269 | 270 | 271 | 272 | 273 | 0 |
| 4 | 280 | 281 | 282 | 283 | 284 | 285 | 0 |
| 5 | 236 | 237 | 238 | 239 | 240 | 241 | 180 |

All zeven screens display the value for the current selection
For the pitch envelope (values 0,1) the same screen is shown, displaying the envelope graph

- Attach, Decay-1, Decay-2, Sustain, Release-1, Release-2, Delay are parameters for the envelope
- Range sets the range of the pitch envelope, in octaves
- Loop selects whether the pitch envelope will loop per operator
- Phase sets the phase for the oscillator per operator (0=0, 1=90, 2=180, 3=270)
- Sync sets the synchronization of the oscillator per operator (free running or sync to note-on)
- Rate sets how the EG times change with the generating MIDI notes
- Velo sets how much the range changes with MIDI velocity
- Wave 1 sets the wave shape for oscillator 1 of the particular operator (range 0-7)
- Ratio sets the frequency ratio between oscillator 1 and 2 of the particular operator
- Wave 2 sets the wave shape for oscillator 2 of the particular operator (range 0-7)

(Range, Rate en Velo zijn nog niet toegekend - ff kijken hoe dit werkt...)
