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

When using fixed pitch operator mode, the frequency is obtained using the following formula: COARSE * FINE:
- COARSE is a value between 0-3, corresponding to 1Hz, 10Hz, 100Hz or 1000Hz;
- FINE is a value between 0-99, corresponding with multipliers 1 to 9.772
The actual formula to get the frequency: Hz = COARSE * (1 + (FINE * 8.772 / 99))

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

## XFM2 conversion

Transpose 24 = no transpose, so 24 corresponds with C4.

Midi note implementation:
- C4 = MIDI 60 = 261.63 Hz
- A4 = MIDI 69 = 440.00 Hz
