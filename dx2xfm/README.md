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

[This article](https://www.muzines.co.uk/articles/understanding-the-dx7/7842) gives a lot of useful insights.

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

### Transpose

Transpose 24 = no transpose, so 24 corresponds with C4.

Midi note implementation:
- C4 = MIDI 60 = 261.63 Hz
- A4 = MIDI 69 = 440.00 Hz
