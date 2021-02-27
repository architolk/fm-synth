# dx2xfm

Conversion code to read a Sysex DX7 file and convert it to XFM2 parameters.

Build: `mvn clean package`

Usage: `./dx2xfm.sh`. This expects a file dx7.syx in the same directory.

## Original DX7 Sysex parameters:

The table below give the DX7 Sysex parameters, as I could find them on the internet.

| Op 6 | Op 5 | Op 4 | Op 3 | Op 2 | Op 1 | Range | Parameter |
|------|------|------|------|------|------|-------|-----------|
| 0 | 21 | 42 | 63 | 84 | 105 | 0-99 | Level Env R1 |
| 1 | 22 | 43 | 64 | 85 | 106 | 0-99 | Level Env R2 |
| 2 | 23 | 44 | 65 | 86 | 107 | 0-99 | Level Env R3 |
| 3 | 24 | 45 | 66 | 87 | 108 | 0-99 | Level Env R4 |
| 4 | 25 | 46 | 67 | 88 | 109 | 0-99 | Level Env L1 |
| 5 | 26 | 47 | 68 | 89 | 110 | 0-99 | Level Env L2 |
| 6 | 27 | 48 | 69 | 90 | 111 | 0-99 | Level Env L3 |
| 7 | 28 | 49 | 70 | 91 | 112 | 0-99 | Level Env L4 |
| 8 | 29 | 50 | 71 | 92 | 113 | 0-99 | Breakpoint? |
| 9 | 30 | 51 | 72 | 93 | 114 | 0-99 | Left depth |
| 10 | 31 | 52 | 73 | 94 | 115 | 0-99 | Right depth |
| 11 | 32 | 53 | 74 | 95 | 116 | 0-3 | Left curve (0=-LIN, 1=-EXP, 2=+EXP, 3=+LIN) |
| 12 | 33 | 54 | 75 | 96 | 117 | 0-3 | Right curve |
| 13 | 34 | 55 | 76 | 97 | 118 | 0-7 | Rate scaling |
| 14 | 35 | 56 | 77 | 98 | 119 | 0-3 | AMP Mod sensitivity |
| 15 | 36 | 57 | 78 | 99 | 120 | 0-7 | Key velocity sensitivity |
| 16 | 37 | 58 | 79 | 100 | 121 | 0-99 | Output level |
| 17 | 38 | 59 | 80 | 101 | 122 | 0-1 | 0=Ratio, 1=Fixed pitch |
| 18 | 39 | 60 | 81 | 102 | 123 | 0-31 | Coarse frequency ratio |
| 19 | 40 | 61 | 82 | 103 | 124 | 0-99 | Fine frequency ratio |
| 20 | 41 | 62 | 83 | 104 | 125 | 0-14 | Detune (7 = 0%) |

| Nr | Range | Parameter |
|----|-------|-----------|
| 126 | 0-99 | Pitch Env R1 |
| 127 | 0-99 | Pitch Env R2 |
| 128 | 0-99 | Pitch Env R3 |
| 129 | 0-99 | Pitch Env R4 |
| 130 | 0-99 | Pitch Env L1 |
| 131 | 0-99 | Pitch Env L2 |
| 132 | 0-99 | Pitch Env L3 |
| 133 | 0-99 | Pitch Env L4 |
| 134 | 0-31 | Algorithm |
| 135 | 0-7 | Feedback |
| 136 | 0-1 | Oscillator sync |
| 137 | 0-99 | LFO Speed |
| 138 | 0-99 | LFO Delay |
| 139 | 0-99 | Pitch mod depth |
| 140 | 0-99 | Amp mod depth |
| 141 | 0-1 | LFO Sync |
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
