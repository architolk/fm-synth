# dx2xfm

Conversion code to read a Sysex DX7 file and convert it to XFM2 parameters.

Build: `mvn clean package`

Usage: `./dx2xfm.sh`. This expects a file dx7.syx in the same directory.

## Original DX7 Sysex parameters:

The table below give the DX7 Sysex parameters, captures from the [original DX7 manual](https://usa.yamaha.com/files/download/other_assets/9/333979/DX7E1.pdf), as is available at [the official Yamaha website](https://usa.yamaha.com/support/manuals/index.html?l=en&c=music_production&k=dx7).

| Op 6 | Op 5 | Op 4 | Op 3 | Op 2 | Op 1 | Range | Parameter |
|------|------|------|------|------|------|-------|-----------|
| 0 | 21 | 42 | 63 | 84 | 105 | 0-99 | Op envelope rate 1 |
| 1 | 22 | 43 | 64 | 85 | 106 | 0-99 | Op envelope rate 2 |
| 2 | 23 | 44 | 65 | 86 | 107 | 0-99 | Op envelope rate 3 |
| 3 | 24 | 45 | 66 | 87 | 108 | 0-99 | Op envelope rate 4 |
| 4 | 25 | 46 | 67 | 88 | 109 | 0-99 | Op envelope level 1 |
| 5 | 26 | 47 | 68 | 89 | 110 | 0-99 | Op envelope level 2 |
| 6 | 27 | 48 | 69 | 90 | 111 | 0-99 | Op envelope level 3 |
| 7 | 28 | 49 | 70 | 91 | 112 | 0-99 | Op envelope level 4 |
| 8 | 29 | 50 | 71 | 92 | 113 | 0-99 | KB level scale breakpoint (from A-1 to C8, C3 = 27) |
| 9 | 30 | 51 | 72 | 93 | 114 | 0-99 | KB level scale, left depth |
| 10 | 31 | 52 | 73 | 94 | 115 | 0-99 | KB level scale, right depth |
| 11 | 32 | 53 | 74 | 95 | 116 | 0-3 | Left curve (0=-LIN, 1=-EXP, 2=+EXP, 3=+LIN) |
| 12 | 33 | 54 | 75 | 96 | 117 | 0-3 | Right curve (0=-LIN, 1=-EXP, 2=+EXP, 3=+LIN) |
| 13 | 34 | 55 | 76 | 97 | 118 | 0-7 | Rate scaling |
| 14 | 35 | 56 | 77 | 98 | 119 | 0-3 | AMP Mod sensitivity |
| 15 | 36 | 57 | 78 | 99 | 120 | 0-7 | Key velocity sensitivity |
| 16 | 37 | 58 | 79 | 100 | 121 | 0-99 | Operator output level |
| 17 | 38 | 59 | 80 | 101 | 122 | 0-1 | 0=Ratio, 1=Fixed pitch |
| 18 | 39 | 60 | 81 | 102 | 123 | 0-31 | Coarse frequency ratio |
| 19 | 40 | 61 | 82 | 103 | 124 | 0-99 | Fine frequency ratio (1.00 - 1.99 multiplier)|
| 20 | 41 | 62 | 83 | 104 | 125 | 0-14 | Detune (7 = 0%) |

| Nr | Range | Parameter |
|----|-------|-----------|
| 126 | 0-99 | Pitch envelope rate 1 |
| 127 | 0-99 | Pitch envelope rate 2 |
| 128 | 0-99 | Pitch envelope rate 3 |
| 129 | 0-99 | Pitch envelope rate 4 |
| 130 | 0-99 | Pitch envelope level 1 |
| 131 | 0-99 | Pitch envelope level 2 |
| 132 | 0-99 | Pitch envelope level 3 |
| 133 | 0-99 | Pitch envelope level 4 |
| 134 | 0-31 | Algorithm |
| 135 | 0-7 | Feedback |
| 136 | 0-1 | Oscillator sync (0=off, 1=on)|
| 137 | 0-99 | LFO Speed |
| 138 | 0-99 | LFO Delay |
| 139 | 0-99 | LFO Pitch mod depth |
| 140 | 0-99 | LFO Amp mod depth |
| 141 | 0-1 | LFO Sync (0=off, 1=on) |
| 142 | 0-5 | LFO Waveform (0:TR, 1:SD, 2:SU, 3:SQ, 4:SI, 5:SH)
| 143 | 0-7 | Pitch mod sensitivity |
| 144 | 0-48 | Transpose (24 = C3) |
| 145 | ASCII | Voice name char 1 |
| 146 | ASCII | Voice name char 2 |
| 147 | ASCII | Voice name char 3 |
| 148 | ASCII | Voice name char 4 |
| 149 | ASCII | Voice name char 5 |
| 150 | ASCII | Voice name char 6 |
| 151 | ASCII | Voice name char 7 |
| 152 | ASCII | Voice name char 8 |
| 153 | ASCII | Voice name char 9 |
| 154 | ASCII | Voice name char 10 |

## Explanation of the DX7 parameters

[Understanding the DX7, Jay Chapman](https://www.muzines.co.uk/articles/understanding-the-dx7/7842) and [How to program the DX7, Bo Tomlyn](https://homepages.abdn.ac.uk/d.j.benson/pages/dx7/manuals/prgrmdx7.pdf) give a lot of useful insights.

Very detailed information about the DX7 envelope generators can be found here:
- [The Yamaha DX7 Envelope Generator, part one](https://tlbflush.org/notes/post/dx7eg1/)
- [The Yamaha DX7 Envelope Generator, part two](https://tlbflush.org/notes/post/dx7eg2/)
- [The Yamaha DX7 Envelope Generator, part three](https://tlbflush.org/notes/post/dx7eg3/)
- [The Yamaha DX7 Envelope Generator, part four](https://tlbflush.org/notes/post/dx7eg4/)

Most important conclusions from this information:
- Both envelope increase and decrease are non-lineair.
- Envelope increase is faster than envelope decrease.
- Envelope decrease is exponential, envelope increase is quadratic.

## XFM2 conversion

### Algorithm

| DX7 | XFM2 |
|-----|------|
| 134 | 1 - 6 |

- The algorithms of the DX7 need to be converted to the bitmapped version for the XFM2.
- Mark that the feedback bit (making a XFM2 operator modulates itself) needs to be included as well!
- Algorithm 4 and 6 have feedback that is not self-modulated (from 4 to 6 and from 5 to 6): so probably operator 6 won't have a feedback bit set!

### Feedback

| DX7 | XFM2 |
|-----|------|
| 135 | 7 - 12 |

- DX7 has only one feedback parameter, range 0-7
- XFM2 has a feedback parameter per operator, range 0-255
- The value from DX7 needs to be copied to the feedback parameter of the XFM2 for the operator that has feedback, according to the algorithm.
- Not tested, but assuming a lineair conversion scale: 255/7
- Not sure: is the feedback parameter used for algorithms 4 and 6, or do these algorithms use the operator output level from operator 4 (for algorithm 4) and operator 5 (for algorithm 6)? We assume the the latter: the XFM2 feedback parameter is only for self modulation!

### Oscillator keyboard sync

| DX7 | XFM2 |
|-----|------|
| 136 | 13 |

- DX7 has global oscillator sync, range 0-1
- XFM2 has bitwise oscillator sync, per operator, LSB = operator 1
- When DX7 has oscillator sync enabled, set the XFM2 oscillator sync parameter to 0b00111111 (=63)

### Operator mode

| DX7 | XFM2 |
|-----|------|
| 17,38,59,80,101,122 | 14 |

- DX7 has a parameter per operator. 0 = ratio, 1 = fixed pitch
- XFM2 has a bitwise parameter. LSB = operator 1. 0 = ratio, 1 = fixed pitch

The conversion for the coarse & fine frequency parameters are different with respect to this parameter!

### Fixed pitch parameter conversion

When using fixed pitch operator mode, the frequency is obtained on the DX7 using the following formula: COARSE * FINE:
- COARSE is a value between 0-3, corresponding to 1Hz, 10Hz, 100Hz or 1000Hz (=HZ-COARSE);
- FINE is a value between 0-99, corresponding with multipliers 1 to 9.772
- The actual formula to get the frequency for the D7 is: Hz = HZ-COARSE * (1 + (FINE * 8.772 / 99))

When using fixed pitch operator mode, the frequency is obtained on the XFM2 using the following formula: COARSE * FINE:
- COARSE is a value between 0-255, frequency is calculated using the formula Hz = COARSE * 32.7
- FINE is a value between 0-255, using the same formula as with frequency fine ratio, so: 2^(FINE/256), for [equal temperament](https://en.wikipedia.org/wiki/Equal_temperament).
- The actual formula to get the frequency for the XFM2 is: Hz = COARSE * 32.7 * 2^(FINE/256)
- An approximation for this formula is: Hz = COARSE * 32.7 * (1 + (FINE/256) * (FINE/256) * 0.34 + (FINE/256) * 0.66)
- The multiplication range for the XFM2 FINE parameter can be calculated from this: it goes from 1 to 1.9946
- Need to check: this would mean that a frequency below 32.7 is not possible using fixed pitch rate. Maybe COARSE = 0 is actually 16.35?

Conversion of coarse & fine parameters in fixed pitch mode needs to be combined: the resulting value for the XFM2 coarse parameter depends on both the coarse & fine parameters of the DX7, for reference see this table:

|DX7 Coarse | DX7 Fine | Hz | XFM2 Coarse | XFM2 Fine |
|-----------|----------|----|-------------|-----------|
| 1 | 0 | 10 Hz | ? | ? |
| 1 | 50 | 54 Hz | 1 | 187 |
| 1 | 99 | 98 Hz | 2 | 148 |
| 2 | 0 | 100 Hz | 3 | 7 |
| 2 | 10 | 189 Hz | 5 | 53 |
| 2 | 99 | 997 Hz | 29 | 11 |
| 3 | 0 | 1000 Hz | 30 | 7 |
| 3 | 10 | 1886 Hz | 57 | 4 |
| 3 | 99 | 9772 Hz | 298 | 1 |

The correct conversion is as follows:
- XFM2-COARSE = Hz / 32.7, rounded down (not using fractions), Hz being the "correct" frequency as calculated for the DX7
- Let HZ-FINE be the fine ratio in Hz needed get to the "correct" frequency: HZ-FINE = (Hz - XFM2-COARSE) / Hz
- XFM2-FINE = 256 / Log2(1 + HZ-FINE)

**NB**: this conversion is ONLY correct for XMF2 Tuning parameter value 0 (= normal tuning = [equal temperament](https://en.wikipedia.org/wiki/Equal_temperament))

### Frequency coarse ratio

| DX7 | XFM2 |
|-----|------|
| 18,39,60,81,102,123 | 15-20 |

- Coarse frequency works the same for DX7 and XFM2
- Range of the XFM2 runs all the way up to 255, DX7 only goes to 31: XFM2 can have higher coarse frequency rates.
- A coarse frequency of 0 on the DX7 is usually depicted as ratio 0.50 (what it actually is: a sub-oscillator)

### Frequency fine ratio

| DX7 | XFM2 |
|-----|------|
| 19,40,61,82,103,124 | 21-26 |

- Fine ratio on the DX7 is a percentage of the frequency. A4 (=440 Hz) with frequency ratio 1.10 (coarse = 1, fine = 10) results in a frequency of 484. The calculation is F = Fc * (1 + Rf/100), F being the resulting frequency, Fc the frequency with only the coarse part and Rf the fine ratio parameter value.
- Fine ratio on the XFM2 is a percentage of an octave. Using [equal temperament](https://en.wikipedia.org/wiki/Equal_temperament), this means that the calculation is actually F = Fc * 2^(Rf/256). So to get the correct ratio, the value is actually fine = 35.
- The correct conversion would be: XFM2 fine = 256 / Log2(1 + Rf/100), Rf being the fine ratio parameter value of the DX7.

**NB**: this conversion is ONLY correct for XMF2 Tuning parameter value 0 (= normal tuning = [equal temperament](https://en.wikipedia.org/wiki/Equal_temperament))

### Detune

| DX7 | XFM2 |
|-----|------|
| 20,41,62,83,104,125 | 27-32 |

- DX7 detune is ranged 0-14, 0 corresponds to -7, 7 corresponds to 0, 14 corresponds to +7
- XFM2 detune is ranged 0-255, 0 corresponeds to -127, 128 corresponds to 0, 127 corresponds to +127
- DX7 detune segments an fine pitch interval of the DX7 (rang -0.007 to +0.007? Not sure..)
- XFM2 detune is ranged in cents, so an interval within a semitone of an octave (see also frequency fine ratio)
- The means: DX7 has detune with respect to frequency, XFM2 has detune with respect to semitones: same different as for frequency fine ratio. But because the intervals are so small, we will probably get away with a fixed conversion ratio.

### Levels

| DX7 | XFM2 |
|-----|------|
| 16,37,58,79,100,121 | 33 - 38 |

- Levels on the DX7 range from 0-99
- Levels on the XFM2 range from 0-255
- Unsure whether the conversion should be linear or some other function. Assumption is linear, so LEVEL * 255/99
- Maybe this info is needed? https://sound.stackexchange.com/questions/31709/what-is-the-level-of-frequency-modulation-of-many-synthesizers

DX7 Levels with respect to modulation index (from FM Theory & Applications, John Chowning):

| DX7 | Index | Approximation |
|-----|-------|---------------|
| 10 | 0.003 | 0.005 |
| 20 | 0.013 | 0.013 |
| 30 | 0.031 | 0.031 |
| 40 | 0.079 | 0.075 |
| 50 | 0.188 | 0.181 |
| 60 | 0.446 | 0.434 |
| 65 | 0.690 | 0.673 |
| 70 | 1.068 | 1.042 |
| 75 | 1.639 | 1.615 |
| 80 | 2.512 | 2.502 |
| 85 | 3.894 | 3.876 |
| 90 | 6.029 | 6.004 |
| 95 | 9.263 | 9.302 |
| 99 | 13.119 | 13.202 |

If we make the assuption that this table would correspond to an exponential function f(x) = ab^(cx), a good approximation can be made using a = 1/440, b = 2.4 and c = 1/10, displayed in the third column.

### Key velocity sensitivity

| DX7 | XMF2 |
|-----|------|
| 15,36,57,78,99,120 | 39 - 44 |

### KB level scale

| Param | DX7 | XFM2 |
|-------|-----|------|
| Breakpoint | 8,29,50,71,92,113 | 45 - 50 |
| Left depth | 9,30,51,72,93,114 | 51 - 56 |
| Right depth | 10,31,52,73,94,115 | 57 - 62 |
| Left curve | 11,32,53,74,95,116 | 63 - 68
| Right curve | 12,33,54,75,96,117 | 69 - 74 |

### Operator level envelope

| Param | DX7 | XFM2 |
|-------|-----|------|
| L1 | 4,25,46,67,88,109 | 75 - 80 |
| L2 | 5,26,47,68,89 | 82 - 87 |
| L3 | 6,27,48,69,90 | 89 - 94 |
| L4 | 7,28,49,70,91,112 | 96 - 101 |
| R1 | 0,21,42,63,84,105 | 103 - 108 |
| R2 | 1,22,43,64,85,106 | 110 - 115 |
| R3 | 2,23,44,65,86,107 | 117 - 122 |
| R4 | 3,24,45,66,87,108 | 124 - 129 |

- The DX7 envelope doesn't start at 0, but at the level of L4, which most of the time will be 0.
- The XFM2 envelope starts at level L0. So to convert the levels correctly: L4 of the DX7 should also be used to calculate L0 of the XFM2:

| Param | DX7 | XFM2 |
|-------|-----|------|
| L0 | 7,28,49,70,91,112 | 181 - 186 |

### Pitch envelope

| Param | DX7 | XFM2 |
|-------|-----|------|
| L1 | 130 | 130 |
| L2 | 131 | 131 |
| L3 | 132 | 132 |
| L4 | 133 | 133 |
| R1 | 126 | 134 |
| R2 | 127 | 135 |
| R3 | 128 | 136 |
| R4 | 129 | 137 |

- The DX7 envelope doesn't start at 0, but at the level of L4, which most of the time will be 0.
- The XFM2 envelope starts at level L0. So to convert the levels correctly: L4 of the DX7 should also be used to calculate L0 of the XFM2:

| Param | DX7 | XFM2 |
|-------|-----|------|
| L0 | 133 | 205 |

### Pitch envelope range

| DX7 | XFM2 |
|-----|------|
| - | 138 |

- The pitch envelope range defines the range of the pitch envelope on the XFM2, in octaves.
- The DX7 doesn't have this parameter. The pitch envelope range is fixed to -4 to +4 octaves (0 = -4, 50 = 0, 99 = -4)

### Pitch envelope range velocity

| DX7 | XFM2 |
|-----|------|
| - | 139 |

- The pitch envelope range velocity sets how much the pitch envelope range changes with MIDI velocity on the XFM2.
- The DX7 doesn't have this parameter. The pitch envelope range is fixed to -4 to +4 octaves.
- Leave this parameter to 0: pitch envelope range velocity is not available on the DX7.

### Operator level envelope rate key

| DX7 | XFM2 |
|-----|------|
| 13,34,55,76,97,118 | 140 - 145 |

- This parameter will make higher notes have a faster envelope than lower, bass, notes. It works rougly the same on the DX7 and XFM2.
- The operator level envelope rate key on the XFM2 works the same as other rates: 0 gives the normal, slowest envelope, 255 gives a very snappy, fast envelope (at high notes).
- The DX7 works the same way, but with a different scale: 0 gives the normal, slowest envelope, 7 gives the fasted envelope (at high notes).

### Pitch envelope rate key

| DX7 | XFM2 |
|-----|------|
| - | 146 |

- The pitch envelope rate key on the XFM2 works the same way as the operator level envelope rate key: changing the timing
- THe DX7 doesn't have this parameter. The pitch envelope timing is fixed.

### LFO Pitch depth

| DX7 | XFM2 |
|-----|------|
| 139 | 149 |

### LFO Amp depth

| DX7 | XFM2 |
|-----|------|
| 140 | 150 |

### LFO Speed

| DX7 | XFM2 |
|-----|------|
| 137 | 151 |

- The LFO speed of the DX7 might go from 0.1 Hz to 60 Hz, but other values are 3.5 Hz to 47 Hz. It seems quite linear at the bottom, but high values seems to increase the speed more than low values.
- The LFO speed of the XFM2 seems pretty linear, a multiplication of 2.76 BPM per parameter value (276 BPM for value 100, 28 BPM for value 10), but higher values also seems to increase the speed?
- The LFO's of the DX7 and XFM2 do not have the same speed range apparently, so some conversion seems to be necessary?

### LFO Sync

| DX7 | XFM2 |
|-----|------|
| 141 | 152 |

### LFO Wave

| DX7 | XFM2 |
|-----|------|
| 142 | 153 |

The DX7 and the XFM2 have the same possible wave forms for the LFO, if you would consider the S/H (Sample & Hold) waveform the same as the random waveform of the XFM2, using the following conversion table:

| Waveform | DX7 | XFM2 |
|----------|-----|------|
| Triangle | 0 | 0 |
| Saw down | 1 | 3 |
| Saw up | 2 | 2 |
| Square | 3 | 1 |
| Sinus | 4 | 4 |
| S/H, Random | 5 | 5 |

### LFO Fade/Delay

| DX7 | XFM2 |
|-----|------|
| 138 | 154 |

- This parameter is called "Fade" on the XFM2 and "Delay" on the DX7. Not sure if it is the same thing.
- From the XFM2 manual, "Fade" is the time to ramp up to the specified LFO effect.
- From the DX7 manaul, "Delay" is simply that: a delay of the LFO effect.
- This assumes that the functionality is somewhat different: a ramp-up effect vs a delayed effect

### LFO Amp sensitivity

| DX7 | XFM2 |
|-----|------|
| 14,35,56,77,98,119 | 159 - 164 |

### Transpose

| DX7 | XFM2 |
|-----|------|
| 144 | 174 |

Transpose 24 = no transpose, so 24 corresponds with C4.

Midi note implementation:
- C4 = MIDI 60 = 261.63 Hz
- A4 = MIDI 69 = 440.00 Hz

### (LFO) Pitch sensitivity

| DX7 | XFM2 |
|-----|------|
| 143 | 222 - 227 |

- The DX7 pitch sensitivity parameter sets the same value for every operator.
- The XFM2 has a pitch sensitivity parameter per operator.

## Conversion reference

The table below gives a reference guide for all 154 parameters of the DX7

| DX7 | Param | XFM2 |
|-----|-------|------|
| 0 | OP-6 Envelope rate 1 | 108 |
| 1 | OP-6 Envelope rate 2 | 115 |
| 2 | OP-6 Envelope rate 3 | 122 |
| 3 | OP-6 Envelope rate 4 | 129 |
| 4 | OP-6 Envelope level 1 | 80 |
| 5 | OP-6 Envelope level 2 | 87 |
| 6 | OP-6 Envelope level 3 | 94 |
| 7 | OP-6 Envelope level 4 | 101 |
| 8 | OP-6 KB level scale breakpoint | 50 |
| 9 | OP-6 KB level scale, left depth | 56 |
| 10 | OP-6 KB level scale, right depth | 62 |
| 11 | OP-6 KB level scale, left curve | 68 |
| 12 | OP-6 KB level scale, right curve | 74 |
| 13 | OP-6 Rate scaling | 145 |
| 14 | OP-6 AMP Mod sensitivity | 164 |
| 15 | OP-6 Key velocity sensitivity | 44 |
| 16 | OP-6 Operator output level | 38 |
| 17 | OP-6 Operator mode (ratio/pitch) | 14 |
| 18 | OP-6 Coarse frequency ratio | 20 |
| 19 | OP-6 Fine frequency ratio | 26 |
| 20 | OP-6 Detune | 32 |
| 21 | OP-5 Envelope rate 1 |  |
| 22 | OP-5 Envelope rate 2 |  |
| 23 | OP-5 Envelope rate 3 |  |
| 24 | OP-5 Envelope rate 4 |  |
| 25 | OP-5 Envelope level 1 |  |
| 26 | OP-5 Envelope level 2 |  |
| 27 | OP-5 Envelope level 3 |  |
| 28 | OP-5 Envelope level 4 |  |
| 29 | OP-5 KB level scale breakpoint |  |
| 30 | OP-5 KB level scale, left depth |  |
| 31 | OP-5 KB level scale, right depth |  |
| 32 | OP-5 Left curve |  |
| 33 | OP-5 Right curve |  |
| 34 | OP-5 Rate scaling |  |
| 35 | OP-5 AMP Mod sensitivity |  |
| 36 | OP-5 Key velocity sensitivity |  |
| 37 | OP-5 Operator output level |  |
| 38 | OP-5 Operator mode (ratio/pitch) |  |
| 39 | OP-5 Coarse frequency ratio |  |
| 40 | OP-5 Fine frequency ratio |  |
| 41 | OP-5 Detune |  |
| 42 | OP-4 Envelope rate 1 |  |
| 43 | OP-4 Envelope rate 2 |  |
| 44 | OP-4 Envelope rate 3 |  |
| 45 | OP-4 Envelope rate 4 |  |
| 46 | OP-4 Envelope level 1 |  |
| 47 | OP-4 Envelope level 2 |  |
| 48 | OP-4 Envelope level 3 |  |
| 49 | OP-4 Envelope level 4 |  |
| 50 | OP-4 KB level scale breakpoint |  |
| 51 | OP-4 KB level scale, left depth |  |
| 52 | OP-4 KB level scale, right depth |  |
| 53 | OP-4 Left curve |  |
| 54 | OP-4 Right curve |  |
| 55 | OP-4 Rate scaling |  |
| 56 | OP-4 AMP Mod sensitivity |  |
| 57 | OP-4 Key velocity sensitivity |  |
| 58 | OP-4 Operator output level |  |
| 59 | OP-4 Operator mode (ratio/pitch) |  |
| 60 | OP-4 Coarse frequency ratio |  |
| 61 | OP-4 Fine frequency ratio |  |
| 62 | OP-4 Detune |  |
| 63 | OP-3 Envelope rate 1 |  |
| 64 | OP-3 Envelope rate 2 |  |
| 65 | OP-3 Envelope rate 3 |  |
| 66 | OP-3 Envelope rate 4 |  |
| 67 | OP-3 Envelope level 1 |  |
| 68 | OP-3 Envelope level 2 |  |
| 69 | OP-3 Envelope level 3 |  |
| 70 | OP-3 Envelope level 4 |  |
| 71 | OP-3 KB level scale breakpoint |  |
| 72 | OP-3 KB level scale, left depth |  |
| 73 | OP-3 KB level scale, right depth |  |
| 74 | OP-3 Left curve |  |
| 75 | OP-3 Right curve |  |
| 76 | OP-3 Rate scaling |  |
| 77 | OP-3 AMP Mod sensitivity |  |
| 78 | OP-3 Key velocity sensitivity |  |
| 79 | OP-3 Operator output level |  |
| 80 | OP-3 Operator mode (ratio/pitch) |  |
| 81 | OP-3 Coarse frequency ratio |  |
| 82 | OP-3 Fine frequency ratio |  |
| 83 | OP-3 Detune |  |
| 84 | OP-2 Envelope rate 1 |  |
| 85 | OP-2 Envelope rate 2 |  |
| 86 | OP-2 Envelope rate 3 |  |
| 87 | OP-2 Envelope rate 4 |  |
| 88 | OP-2 Envelope level 1 |  |
| 89 | OP-2 Envelope level 2 |  |
| 90 | OP-2 Envelope level 3 |  |
| 91 | OP-2 Envelope level 4 |  |
| 92 | OP-2 KB level scale breakpoint |  |
| 93 | OP-2 KB level scale, left depth |  |
| 94 | OP-2 KB level scale, right depth |  |
| 95 | OP-2 Left curve |  |
| 96 | OP-2 Right curve |  |
| 97 | OP-2 Rate scaling |  |
| 98 | OP-2 AMP Mod sensitivity |  |
| 99 | OP-2 Key velocity sensitivity |  |
| 100 | OP-2 Operator output level |  |
| 101 | OP-2 Operator mode (ratio/pitch) |  |
| 102 | OP-2 Coarse frequency ratio |  |
| 103 | OP-2 Fine frequency ratio |  |
| 104 | OP-2 Detune |  |
| 105 | OP-1 Envelope rate 1 |  |
| 106 | OP-1 Envelope rate 2 |  |
| 107 | OP-1 Envelope rate 3 |  |
| 108 | OP-1 Envelope rate 4 |  |
| 109 | OP-1 Envelope level 1 |  |
| 110 | OP-1 Envelope level 2 |  |
| 111 | OP-1 Envelope level 3 |  |
| 112 | OP-1 Envelope level 4 |  |
| 113 | OP-1 KB level scale breakpoint |  |
| 114 | OP-1 KB level scale, left depth |  |
| 115 | OP-1 KB level scale, right depth |  |
| 116 | OP-1 Left curve |  |
| 117 | OP-1 Right curve |  |
| 118 | OP-1 Rate scaling |  |
| 119 | OP-1 AMP Mod sensitivity |  |
| 120 | OP-1 Key velocity sensitivity |  |
| 121 | OP-1 Operator output level |  |
| 122 | OP-1 Operator mode (ratio/pitch) |  |
| 123 | OP-1 Coarse frequency ratio |  |
| 124 | OP-1 Fine frequency ratio |  |
| 125 | OP-1 Detune |  |
| 126 | Pitch envelope rate 1 | 134 |
| 127 | Pitch envelope rate 2 | 135 |
| 128 | Pitch envelope rate 3 | 136 |
| 129 | Pitch envelope rate 4 | 137 |
| 130 | Pitch envelope level 1 | 130 |
| 131 | Pitch envelope level 2 | 131 |
| 132 | Pitch envelope level 3 | 132 |
| 133 | Pitch envelope level 4 | 133 |
| 134 | Algorithm | 1 - 6 |
| 135 | Feedback | 7 - 12 |
| 136 | Oscillator sync | 13 |
| 137 | LFO Speed | 151 |
| 138 | LFO Delay | 154 |
| 139 | LFO Pitch mod depth | 149 |
| 140 | LFO Amp mod depth | 150 |
| 141 | LFO Sync | 152 |
| 142 | LFO Waveform | 153 |
| 143 | Pitch mod sensitivity | 222 - 227 |
| 144 | Transpose | 174 |
| 145 | Voice name char 1 | - |
| 146 | Voice name char 2 | - |
| 147 | Voice name char 3 | - |
| 148 | Voice name char 4 | - |
| 149 | Voice name char 5 | - |
| 150 | Voice name char 6 | - |
| 151 | Voice name char 7 | - |
| 152 | Voice name char 8 | - |
| 153 | Voice name char 9 | - |
| 154 | Voice name char 10 | - |
