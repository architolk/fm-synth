# XFM2 params

This page gives an overview of all XFM2 parameters. It is a cross-reference to the assignment at the physical hardware level, to be sure that every parameter is covered.

- A *italic* item in the table below for the Blue buttons indicate that this option has two different parameters you can change. You need to toggle between these two parameters (by pressing the corresponding blue button again). The one you selected is marked with a bar below the corresponding parameter.
- **Op-1 dial** corresponds to turning the Op-1 dial. **Op dials** means that the parameter contains a bitwise setting for all operators, so a particular Op dial changes the parameter with respect to the corresponding operator.
- **Op dials click** corresponds to pressing an operator dial (using it as a push button).
- **Op-1 selected** corresponds to selecting operator-1 envelope. For the operator level envelopes, you select a particular operator by pressing the corresponding operator dial. To change the particular parameter, you use the corresponding dial for that parameter (as depicted at the bottom of the synth). This might be some *other* dial than the dial that corresponds to that operator!
- Most parameters work for both Unit #1 and Unit #2: you switch between units by selecting the corresponding **green** option. The exception are some parameters that are controlled by the master mixer, as depicted in the table below:

| Blue | Assignment | Unit |
|------|------------|------|
| Pitch | Velocity sensitivity | 1 |
| Feedback | Velocity sensitivity | 2 |
| Duration | Mixer | 1 |
| Level | Mixer | 2 |

| Nr | Parameter | Green | Blue | Assignment |
|----|-----------|-------|------|------------|
| 0 | NOP | - | - | - |
| 1 | Algorithm Op-1 | - | - | Orange & Red LEDs, Op-1 row |
| 2 | Algorithm Op-2 | - | - | Orange & Red LEDs, Op-2 row |
| 3 | Algorithm Op-3 | - | - | Orange & Red LEDs, Op-3 row |
| 4 | Algorithm Op-4 | - | - | Orange & Red LEDs, Op-4 row |
| 5 | Algorithm Op-5 | - | - | Orange & Red LEDs, Op-5 row |
| 6 | Algorithm Op-6 | - | - | Orange & Red LEDs, Op-6 row |
| 7 | Feedback Op-1 | - | Feedback | Op-1 dial |
| 8 | Feedback Op-2 | - | Feedback | Op-2 dial |
| 9 | Feedback Op-3 | - | Feedback | Op-3 dial |
| 10 | Feedback Op-4 | - | Feedback | Op-4 dial |
| 11 | Feedback Op-5 | - | Feedback | Op-5 dial |
| 12 | Feedback Op-6 | - | Feedback | Op-6 dial |
| 13 | Oscillator sync | OSC | *Feedback* | Op dials |
| 14 | Operator mode | OPS | Pitch | Op dials click |
| 15 | Coarse ratio Op-1 | OPS | *Ratio* | Op-1 dial |
| 16 | Coarse ratio Op-2 | OPS | *Ratio* | Op-2 dial |
| 17 | Coarse ratio Op-3 | OPS | *Ratio* | Op-3 dial |
| 18 | Coarse ratio Op-4 | OPS | *Ratio* | Op-4 dial |
| 19 | Coarse ratio Op-5 | OPS | *Ratio* | Op-5 dial |
| 20 | Coarse ratio Op-6 | OPS | *Ratio* | Op-6 dial |
| 21 | Fine ratio Op-1 | OPS | *Ratio* | Op-1 dial |
| 22 | Fine ratio Op-2 | OPS | *Ratio* | Op-2 dial |
| 23 | Fine ratio Op-3 | OPS | *Ratio* | Op-3 dial |
| 24 | Fine ratio Op-4 | OPS | *Ratio* | Op-4 dial |
| 25 | Fine ratio Op-5 | OPS | *Ratio* | Op-5 dial |
| 26 | Fine ratio Op-6 | OPS | *Ratio* | Op-6 dial |
| 27 | Detune Op-1 | OSC | Pitch | Op-1 dial |
| 28 | Detune Op-2 | OSC | Pitch | Op-2 dial |
| 29 | Detune Op-3 | OSC | Pitch | Op-3 dial |
| 30 | Detune Op-4 | OSC | Pitch | Op-4 dial |
| 31 | Detune Op-5 | OSC | Pitch | Op-5 dial |
| 32 | Detune Op-6 | OSC | Pitch | Op-6 dial |
| 33 | Level Op-1 | OSC | Volume | Op-1 dial |
| 34 | Level Op-2 | OSC | Volume | Op-2 dial |
| 35 | Level Op-3 | OSC | Volume | Op-3 dial |
| 36 | Level Op-4 | OSC | Volume | Op-4 dial |
| 37 | Level Op-5 | OSC | Volume | Op-5 dial |
| 38 | Level Op-6 | OSC | Volume | Op-6 dial |
| 39 | Velo sense Op-1 | Master | Pitch/Feedback | Op-1 dial |
| 40 | Velo sense Op-2 | Master | Pitch/Feedback | Op-2 dial |
| 41 | Velo sense Op-3 | Master | Pitch/Feedback | Op-3 dial |
| 42 | Velo sense Op-4 | Master | Pitch/Feedback | Op-4 dial |
| 43 | Velo sense Op-5 | Master | Pitch/Feedback | Op-5 dial |
| 44 | Velo sense Op-6 | Master | Pitch/Feedback | Op-6 dial |
| 45 | KB level scale breakpoint Op-1 | LFO | Pitch | Op-1 dial |
| 46 | KB level scale breakpoint Op-2 | LFO | Pitch | Op-2 dial |
| 47 | KB level scale breakpoint Op-3 | LFO | Pitch | Op-3 dial |
| 48 | KB level scale breakpoint Op-4 | LFO | Pitch | Op-4 dial |
| 49 | KB level scale breakpoint Op-5 | LFO | Pitch | Op-5 dial |
| 50 | KB level scale breakpoint Op-6 | LFO | Pitch | Op-6 dial |
| 51 | KB level scale, left depth Op-1 | LFO | *Ratio* | Op-1 dial |
| 52 | KB level scale, left depth Op-2 | LFO | *Ratio* | Op-2 dial |
| 53 | KB level scale, left depth Op-3 | LFO | *Ratio* | Op-3 dial |
| 54 | KB level scale, left depth Op-4 | LFO | *Ratio* | Op-4 dial |
| 55 | KB level scale, left depth Op-5 | LFO | *Ratio* | Op-5 dial |
| 56 | KB level scale, left depth Op-6 | LFO | *Ratio* | Op-6 dial |
| 57 | KB level scale, right depth Op-1 | LFO | *Feedback* | Op-1 dial |
| 58 | KB level scale, right depth Op-2 | LFO | *Feedback* | Op-2 dial |
| 59 | KB level scale, right depth Op-3 | LFO | *Feedback* | Op-3 dial |
| 60 | KB level scale, right depth Op-4 | LFO | *Feedback* | Op-4 dial |
| 61 | KB level scale, right depth Op-5 | LFO | *Feedback* | Op-5 dial |
| 62 | KB level scale, right depth Op-6 | LFO | *Feedback* | Op-6 dial |
| 63 | KB level scale, left curve Op-1 | LFO | *Ratio* | Op-1 dial |
| 64 | KB level scale, left curve Op-2 | LFO | *Ratio* | Op-2 dial |
| 65 | KB level scale, left curve Op-3 | LFO | *Ratio* | Op-3 dial |
| 66 | KB level scale, left curve Op-4 | LFO | *Ratio* | Op-4 dial |
| 67 | KB level scale, left curve Op-5 | LFO | *Ratio* | Op-5 dial |
| 68 | KB level scale, left curve Op-6 | LFO | *Ratio* | Op-6 dial |
| 69 | KB level scale, right curve Op-1 | LFO | *Feedback* | Op-1 dial |
| 70 | KB level scale, right curve Op-2 | LFO | *Feedback* | Op-2 dial |
| 71 | KB level scale, right curve Op-3 | LFO | *Feedback* | Op-3 dial |
| 72 | KB level scale, right curve Op-4 | LFO | *Feedback* | Op-4 dial |
| 73 | KB level scale, right curve Op-5 | LFO | *Feedback* | Op-5 dial |
| 74 | KB level scale, right curve Op-6 | LFO | *Feedback* | Op-6 dial |
| 75 | Envelope level 1, Op-1 | OPS | Level | Op-1 dial (attack) / Op-1 selected |
| 76 | Envelope level 1, Op-1 | OPS | Level | Op-1 dial (attack) / Op-2 selected |
| 77 | Envelope level 1, Op-1 | OPS | Level | Op-1 dial (attack) / Op-3 selected |
| 78 | Envelope level 1, Op-1 | OPS | Level | Op-1 dial (attack) / Op-4 selected |
| 79 | Envelope level 1, Op-1 | OPS | Level | Op-1 dial (attack) / Op-5 selected |
| 80 | Envelope level 1, Op-1 | OPS | Level | Op-1 dial (attack) / Op-6 selected |
| 81 | NOP | - | - | - |
| 82 | Envelope level 2, Op-1 | OPS | Level | Op-2 dial (decay-1) / Op-1 selected |
| 83 | Envelope level 2, Op-1 | OPS | Level | Op-2 dial (decay-1) / Op-2 selected |
| 84 | Envelope level 2, Op-1 | OPS | Level | Op-2 dial (decay-1) / Op-3 selected |
| 85 | Envelope level 2, Op-1 | OPS | Level | Op-2 dial (decay-1) / Op-4 selected |
| 86 | Envelope level 2, Op-1 | OPS | Level | Op-2 dial (decay-1) / Op-5 selected |
| 87 | Envelope level 2, Op-1 | OPS | Level | Op-2 dial (decay-1) / Op-6 selected |
| 88 | NOP | - | - | - |
| 89 | Envelope level 3, Op-1 | OPS | Level | Op-4 dial (sustain) / Op-1 selected |
| 90 | Envelope level 3, Op-1 | OPS | Level | Op-4 dial (sustain) / Op-2 selected |
| 91 | Envelope level 3, Op-1 | OPS | Level | Op-4 dial (sustain) / Op-3 selected |
| 92 | Envelope level 3, Op-1 | OPS | Level | Op-4 dial (sustain) / Op-4 selected |
| 93 | Envelope level 3, Op-1 | OPS | Level | Op-4 dial (sustain) / Op-5 selected |
| 94 | Envelope level 3, Op-1 | OPS | Level | Op-4 dial (sustain) / Op-6 selected |
| 95 | NOP | - | - | - |
| 96 | Envelope level 4, Op-1 | OPS | Level | Op-5 dial (release-1) / Op-1 selected |
| 97 | Envelope level 4, Op-1 | OPS | Level | Op-5 dial (release-1) / Op-2 selected |
| 98 | Envelope level 4, Op-1 | OPS | Level | Op-5 dial (release-1) / Op-3 selected |
| 99 | Envelope level 4, Op-1 | OPS | Level | Op-5 dial (release-1) / Op-4 selected |
| 100 | Envelope level 4, Op-1 | OPS | Level | Op-5 dial (release-1) / Op-5 selected |
| 101 | Envelope level 4, Op-1 | OPS | Level | Op-5 dial (release-1) / Op-6 selected |
| 102 | NOP | - | - | - |
| 103 | Envelope rate 1, Op-1 | OPS | Duration | Op-1 dial (attack) / Op-1 selected |
| 104 | Envelope rate 1, Op-1 | OPS | Duration | Op-1 dial (attack) / Op-2 selected |
| 105 | Envelope rate 1, Op-1 | OPS | Duration | Op-1 dial (attack) / Op-3 selected |
| 106 | Envelope rate 1, Op-1 | OPS | Duration | Op-1 dial (attack) / Op-4 selected |
| 107 | Envelope rate 1, Op-1 | OPS | Duration | Op-1 dial (attack) / Op-5 selected |
| 108 | Envelope rate 1, Op-1 | OPS | Duration | Op-1 dial (attack) / Op-6 selected |
| 109 | NOP | - | - | - |
| 110 | Envelope rate 2, Op-1 | OPS | Duration | Op-2 dial (decay-1) / Op-1 selected |
| 111 | Envelope rate 2, Op-1 | OPS | Duration | Op-2 dial (decay-1) / Op-2 selected |
| 112 | Envelope rate 2, Op-1 | OPS | Duration | Op-2 dial (decay-1) / Op-3 selected |
| 113 | Envelope rate 2, Op-1 | OPS | Duration | Op-2 dial (decay-1) / Op-4 selected |
| 114 | Envelope rate 2, Op-1 | OPS | Duration | Op-2 dial (decay-1) / Op-5 selected |
| 115 | Envelope rate 2, Op-1 | OPS | Duration | Op-2 dial (decay-1) / Op-6 selected |
| 116 | NOP | - | - | - |
| 117 | Envelope rate 3, Op-1 | OPS | Duration | Op-3 dial (decay-2) / Op-1 selected |
| 118 | Envelope rate 3, Op-1 | OPS | Duration | Op-3 dial (decay-2) / Op-2 selected |
| 119 | Envelope rate 3, Op-1 | OPS | Duration | Op-3 dial (decay-2) / Op-3 selected |
| 120 | Envelope rate 3, Op-1 | OPS | Duration | Op-3 dial (decay-2) / Op-4 selected |
| 121 | Envelope rate 3, Op-1 | OPS | Duration | Op-3 dial (decay-2) / Op-5 selected |
| 122 | Envelope rate 3, Op-1 | OPS | Duration | Op-3 dial (decay-2) / Op-6 selected |
| 123 | NOP | - | - | - |
| 124 | Envelope rate 4, Op-1 | OPS | Duration | Op-5 dial (release-1) / Op-1 selected |
| 125 | Envelope rate 4, Op-1 | OPS | Duration | Op-5 dial (release-1) / Op-2 selected |
| 126 | Envelope rate 4, Op-1 | OPS | Duration | Op-5 dial (release-1) / Op-3 selected |
| 127 | Envelope rate 4, Op-1 | OPS | Duration | Op-5 dial (release-1) / Op-4 selected |
| 128 | Envelope rate 4, Op-1 | OPS | Duration | Op-5 dial (release-1) / Op-5 selected |
| 129 | Envelope rate 4, Op-1 | OPS | Duration | Op-5 dial (release-1) / Op-6 selected |
| 130 | Pitch envelope level 1 | OSC | Level | Op-1 dial (attack) |
| 131 | Pitch envelope level 2 | OPS | Level | Op-2 dial (decay-1) |
| 132 | Pitch envelope level 3 | OPS | Level | Op-4 dial (sustain) |
| 133 | Pitch envelope level 4 | OPS | Level | Op-5 dial (release-1) |
| 134 | Pitch envelope rate 1 | OSC | Level | Op-1 dial (attack) |
| 135 | Pitch envelope rate 2 | OPS | Level | Op-2 dial (decay-1) |
| 136 | Pitch envelope rate 3 | OPS | Level | Op-4 dial (decay-2) |
| 137 | Pitch envelope rate 4 | OPS | Level | Op-5 dial (release-1) |
| 138 | Pitch envelope range | ? | ? | ? |
| 139 | Pitch envelope range velocity | ? | ? | ? |
| 140 | Envelope rate key, Op-1 | ? | ? | ? |
| 141 | Envelope rate key, Op-2 | ? | ? | ? |
| 142 | Envelope rate key, Op-3 | ? | ? | ? |
| 143 | Envelope rate key, Op-4 | ? | ? | ? |
| 144 | Envelope rate key, Op-5 | ? | ? | ? |
| 145 | Envelope rate key, Op-6 | ? | ? | ? |
| 146 | Pitch envelope rate key | ? | ? | ? |
| 147 | NOP | - | - | - |
| 148 | NOP | - | - | - |
| 149 | LFO pitch depth | LFO | Volume | Op-5 dial |
| 150 | LFO amplitude depth | LFO | Volume | Op-6 dial |
| 151 | LFO speed | LFO | Volume | Op-2 dial |
| 152 | LFO sync | LFO | *Volume* | Op-3 dial |
| 153 | LFO wave | LFO | Volume | Op-1 dial |
| 154 | LFO fade | LFO | Volume | Op-4 dial |
| 155 | LFO pitch depth wheel | ? | ? | ? |
| 156 | LFO amp depth wheel | ? | ? | ? |
| 157 | LFO pitch depth aftertouch | ? | ? | ? |
| 158 | LFO amp depth aftertouch | ? | ? | ? |
| 159 | LFO amp sense, Op-1 | LFO | Level | Op-1 dial |
| 160 | LFO amp sense, Op-2 | LFO | Level | Op-2 dial |
| 161 | LFO amp sense, Op-3 | LFO | Level | Op-3 dial |
| 162 | LFO amp sense, Op-4 | LFO | Level | Op-4 dial |
| 163 | LFO amp sense, Op-5 | LFO | Level | Op-5 dial |
| 164 | LFO amp sense, Op-6 | LFO | Level | Op-6 dial |
| 165 | NOP | - | - | - |
| 166 | NOP | - | - | - |
| 167 | NOP | - | - | - |
| 168 | NOP | - | - | - |
| 169 | NOP | - | - | - |
| 170 | NOP | - | - | - |
| 171 | NOP | - | - | - |
| 172 | Bend range up | ? | ? | ? |
| 173 | Bend range down | ? | ? | ? |
| 174 | Transpose | Master | Volume | Op-2 dial |
| 175 | NOP | - | - | - |
| 176 | NOP | - | - | - |
| 177 | NOP | - | - | - |
| 178 | NOP | - | - | - |
| 179 | NOP | - | - | - |
| 180 | Volume | OSC | Volume | Output dial |
| 181 | Envelope level 0, Op-1 | OPS | Level | Output dial (delay) / Op-1 selected |
| 182 | Envelope level 0, Op-2 | OPS | Level | Output dial (delay) / Op-2 selected |
| 183 | Envelope level 0, Op-3 | OPS | Level | Output dial (delay) / Op-3 selected |
| 184 | Envelope level 0, Op-4 | OPS | Level | Output dial (delay) / Op-4 selected |
| 185 | Envelope level 0, Op-5 | OPS | Level | Output dial (delay) / Op-5 selected |
| 186 | Envelope level 0, Op-6 | OPS | Level | Output dial (delay) / Op-6 selected |
| 187 | Envelope rate 0, Op-1 | OPS | Duration | Output dial (delay) / Op-1 selected |
| 188 | Envelope rate 0, Op-2 | OPS | Duration | Output dial (delay) / Op-2 selected |
| 189 | Envelope rate 0, Op-3 | OPS | Duration | Output dial (delay) / Op-3 selected |
| 190 | Envelope rate 0, Op-4 | OPS | Duration | Output dial (delay) / Op-4 selected |
| 191 | Envelope rate 0, Op-5 | OPS | Duration | Output dial (delay) / Op-5 selected |
| 192 | Envelope rate 0, Op-6 | OPS | Duration | Output dial (delay) / Op-6 selected |
| 193 | Envelope level 5, Op-1 | OPS | Level | Op-6 dial (release-2) / Op-1 selected |
| 194 | Envelope level 5, Op-2 | OPS | Level | Op-6 dial (release-2) / Op-2 selected |
| 195 | Envelope level 5, Op-3 | OPS | Level | Op-6 dial (release-2) / Op-3 selected |
| 196 | Envelope level 5, Op-4 | OPS | Level | Op-6 dial (release-2) / Op-4 selected |
| 197 | Envelope level 5, Op-5 | OPS | Level | Op-6 dial (release-2) / Op-5 selected |
| 198 | Envelope level 5, Op-6 | OPS | Level | Op-6 dial (release-2) / Op-6 selected |
| 199 | Envelope rate 5, Op-1 | OPS | Duration | Op-6 dial (release-2) / Op-1 selected |
| 200 | Envelope rate 5, Op-2 | OPS | Duration | Op-6 dial (release-2) / Op-2 selected |
| 201 | Envelope rate 5, Op-3 | OPS | Duration | Op-6 dial (release-2) / Op-3 selected |
| 202 | Envelope rate 5, Op-4 | OPS | Duration | Op-6 dial (release-2) / Op-4 selected |
| 203 | Envelope rate 5, Op-5 | OPS | Duration | Op-6 dial (release-2) / Op-5 selected |
| 204 | Envelope rate 5, Op-6 | OPS | Duration | Op-6 dial (release-2) / Op-6 selected |
| 205 | Pitch envelope level 0 | OSC | Level | Output dial (delay) |
| 206 | Pitch envelope rate 0 | OSC | Duration | Output dial (delay) |
| 207 | Pitch envelope level 5 | OSC | Level | Op-6 dial (release-2) |
| 208 | Pitch envelope rate 5 | OSC | Duration | Op-6 dial (release-2) |
| 209 | LFO Pitch depth breath | ? | ? | ? |
| 210 | LFO Amp depth breath | ? | ? | ? |
| 211 | LFO Pitch depth foot | ? | ? | ? |
| 212 | LFO Amp depth foot | ? | ? | ? |
| 213 | Volume depth aftertouch | ? | ? | ? |
| 214 | Volume depth wheel | ? | ? | ? |
| 215 | Volume depth breath | ? | ? | ? |
| 216 | Volume depth foot | ? | ? | ? |
| 217 | Pitch depth aftertouch | ? | ? | ? |
| 218 | Pitch depth breath | ? | ? | ? |
| 219 | Pitch depth foot | ? | ? | ? |
| 220 | Pitch depth rnd | ? | ? | ? |
| 221 | Pan | Master | Volume | Op-1 dial |
| 222 | LFO pitch sense, Op-1 | LFO | Duration | Op-1 dial |
| 223 | LFO pitch sense, Op-2 | LFO | Duration | Op-2 dial |
| 224 | LFO pitch sense, Op-3 | LFO | Duration | Op-3 dial |
| 225 | LFO pitch sense, Op-4 | LFO | Duration | Op-4 dial |
| 226 | LFO pitch sense, Op-5 | LFO | Duration | Op-5 dial |
| 227 | LFO pitch sense, Op-6 | LFO | Duration | Op-6 dial |
| 228 | Legato (mono/poly) | Master | Volume | Op-3 dial |
| 229 | Portamento (glide) mode | Master | Volume | Op-5 dial |
| 230 | Portamento (glide) time | Master | Volume | Op-4 dial |
| 231 | NOP | - | - | - |
| 232 | NOP | - | - | - |
| 233 | NOP | - | - | - |
| 234 | NOP | - | - | - |
| 235 | NOP | - | - | - |
| 236 | Oscillator 1 wave, Op-1 | OSC | Volume | Op-1 dial |
| 237 | Oscillator 1 wave, Op-2 | OSC | Volume | Op-2 dial |
| 238 | Oscillator 1 wave, Op-3 | OSC | Volume | Op-3 dial |
| 239 | Oscillator 1 wave, Op-4 | OSC | Volume | Op-4 dial |
| 240 | Oscillator 1 wave, Op-5 | OSC | Volume | Op-5 dial |
| 241 | Oscillator 1 wave, Op-6 | OSC | Volume | Op-6 dial |
| 242 | Velocity offset | Master | Pitch/Feedback | Output dial |
| 243 | Velocity curve | ? | ? | ? |
| 244 | Envelope loop | ? | ? | ? |
| 245 | Envelope loop segment | ? | ? | ? |
| 246 | Envelope restart | ? | ? | ? |
| 247 | NOP | - | - | - |
| 248 | NOP | - | - | - |
| 249 | NOP | - | - | - |
| 250 | NOP | - | - | - |
| 251 | Tuning | Master | Volume | Op-6 dial |
| 252 | Waveset | ? | ? | ? |
| 253 | NOP | - | - | - |
| 254 | NOP | - | - | - |
| 255 | NOP | - | - | - |
| 256 | Left level Op-1 | Master | *Duration/Level* | Op-1 dial |
| 257 | Right level, Op-1 | Master | *Duration/Level* | Op-1 dial |
| 258 | Left level, Op-2 | Master | *Duration/Level* | Op-2 dial |
| 259 | Right level, Op-2 | Master | *Duration/Level* | Op-2 dial |
| 260 | Left level Op-3 | Master | *Duration/Level* | Op-3 dial |
| 261 | Right level, Op-3 | Master | *Duration/Level* | Op-3 dial |
| 262 | Left level, Op-4 | Master | *Duration/Level* | Op-4 dial |
| 263 | Right level, Op-4 | Master | *Duration/Level* | Op-4 dial |
| 264 | Left level Op-5 | Master | *Duration/Level* | Op-5 dial |
| 265 | Right level, Op-5 | Master | *Duration/Level* | Op-5 dial |
| 266 | Left level, Op-6 | Master | *Duration/Level* | Op-6 dial |
| 267 | Right level, Op-6 | Master | *Duration/Level* | Op-6 dial |
| 268 | Oscillator 2 wave, Op-1 | OSC | Pitch | Op-1 dial |
| 269 | Oscillator 2 wave, Op-2 | OSC | Pitch | Op-2 dial |
| 270 | Oscillator 2 wave, Op-3 | OSC | Pitch | Op-3 dial |
| 271 | Oscillator 2 wave, Op-4 | OSC | Pitch | Op-4 dial |
| 272 | Oscillator 2 wave, Op-5 | OSC | Pitch | Op-5 dial |
| 273 | Oscillator 2 wave, Op-6 | OSC | Pitch | Op-6 dial |
| 274 | Oscillator wave mode , Op-1 | OSC | *Ratio* | Op-1 dial |
| 275 | Oscillator wave mode , Op-2 | OSC | *Ratio* | Op-2 dial |
| 276 | Oscillator wave mode , Op-3 | OSC | *Ratio* | Op-3 dial |
| 277 | Oscillator wave mode , Op-4 | OSC | *Ratio* | Op-4 dial |
| 278 | Oscillator wave mode , Op-5 | OSC | *Ratio* | Op-5 dial |
| 279 | Oscillator wave mode , Op-6 | OSC | *Ratio* | Op-6 dial |
| 280 | Oscillator wave ratio , Op-1 | OSC | *Ratio* | Op-1 dial |
| 281 | Oscillator wave ratio , Op-2 | OSC | *Ratio* | Op-2 dial |
| 282 | Oscillator wave ratio , Op-3 | OSC | *Ratio* | Op-3 dial |
| 283 | Oscillator wave ratio , Op-4 | OSC | *Ratio* | Op-4 dial |
| 284 | Oscillator wave ratio , Op-5 | OSC | *Ratio* | Op-5 dial |
| 285 | Oscillator wave ratio , Op-6 | OSC | *Ratio* | Op-6 dial |
| 286 | Oscillator phase , Op-1 | OSC | *Feedback* | Op-1 dial |
| 287 | Oscillator phase , Op-2 | OSC | *Feedback* | Op-2 dial |
| 288 | Oscillator phase , Op-3 | OSC | *Feedback* | Op-3 dial |
| 289 | Oscillator phase , Op-4 | OSC | *Feedback* | Op-4 dial |
| 290 | Oscillator phase , Op-5 | OSC | *Feedback* | Op-5 dial |
| 291 | Oscillator phase , Op-6 | OSC | *Feedback* | Op-6 dial |
| 292 | NOP | - | - | - |
| 293 | NOP | - | - | - |
| 294 | NOP | - | - | - |
| 295 | NOP | - | - | - |
| 296 | NOP | - | - | - |
| 297 | NOP | - | - | - |
| 298 | NOP | - | - | - |
| 299 | NOP | - | - | - |
| 300 | EFX Delay dry | EFX | Delay | ? |
| 301 | EFX Delay wet | EFX | Delay | ? |
| 302 | EFX Delay mode | EFX | Delay | ? |
| 303 | EFX Delay time | EFX | Delay | ? |
| 304 | EFX Delay feedback | EFX | Delay | ? |
| 305 | EFX Delay feedback lo filter | EFX | Delay | ? |
| 306 | EFX Delay feedback hi filter | EFX | Delay | ? |
| 307 | EFX Delay tempo | EFX | Delay | ? |
| 308 | EFX Delay num | EFX | Delay | ? |
| 309 | EFX Delay den | EFX | Delay | ? |
| 310 | EFX Phaser dry | EFX | Phaser | ? |
| 311 | EFX Phaser wet | EFX | Phaser | ? |
| 312 | EFX Phaser mode | EFX | Phaser | ? |
| 313 | EFX Phaser depth | EFX | Phaser | ? |
| 314 | EFX Phaser speed | EFX | Phaser | ? |
| 315 | EFX Phaser feedback | EFX | Phaser | ? |
| 316 | EFX Phaser offset | EFX | Phaser | ? |
| 317 | EFX Phaser stages | EFX | Phaser | ? |
| 318 | EFX Phaser phase | EFX | Phaser | ? |
| 319 | EFX Phaser waveform | EFX | Phaser | - |
| 320 | EFX Filter low pass | EFX | EFX | ? |
| 321 | EFX Filter high pass | EFX | EFX | ? |
| 322 | NOP | - | - | - |
| 323 | NOP | - | - | - |
| 324 | NOP | - | - | - |
| 325 | NOP | - | - | - |
| 326 | NOP | - | - | - |
| 327 | NOP | - | - | - |
| 328 | NOP | - | - | - |
| 329 | NOP | - | - | - |
| 330 | EFX AM speed | EFX | AM | ? |
| 331 | EFX AM range | EFX | AM | ? |
| 332 | EFX AM depth | EFX | AM | ? |
| 333 | EFX AM phase | EFX | AM | ? |
| 334 | NOP | - | - | - |
| 335 | NOP | - | - | - |
| 336 | NOP | - | - | - |
| 337 | NOP | - | - | - |
| 338 | NOP | - | - | - |
| 339 | NOP | - | - | - |
| 340 | EFX FIR Impulse | - | - | - |
| 341 | NOP | - | - | - |
| 342 | NOP | - | - | - |
| 343 | NOP | - | - | - |
| 344 | NOP | - | - | - |
| 345 | NOP | - | - | - |
| 346 | NOP | - | - | - |
| 347 | NOP | - | - | - |
| 348 | NOP | - | - | - |
| 349 | NOP | - | - | - |
| 350 | EFX Waveshaper dry | - | - | - |
| 351 | EFX Waveshaper wet | - | - | - |
| 352 | EFX Waveshaper gain pre | - | - | - |
| 353 | EFX Waveshaper gain post | - | - | - |
| 354 | EFX Waveshaper shape | - | - | - |
| 355 | NOP | - | - | - |
| 356 | NOP | - | - | - |
| 357 | NOP | - | - | - |
| 358 | NOP | - | - | - |
| 359 | NOP | - | - | - |
| 360 | EFX Chorus dry | EFX | Chorus | ? |
| 361 | EFX Chorus wet | EFX | Chorus | ? |
| 362 | EFX Chorus mode | EFX | Chorus | ? |
| 363 | EFX Chorus speed | EFX | Chorus | ? |
| 364 | EFX Chorus depth | EFX | Chorus | ? |
| 365 | EFX Chorus feedback | EFX | Chorus | ? |
| 366 | EFX Chorus phase | EFX | Chorus | ? |
| 367 | NOP | - | - | - |
| 368 | NOP | - | - | - |
| 369 | NOP | - | - | - |
| 370 | EFX Decimator depth | EFX | EFX | ? |
| 371 | NOP | - | - | - |
| 372 | NOP | - | - | - |
| 373 | NOP | - | - | - |
| 374 | NOP | - | - | - |
| 375 | NOP | - | - | - |
| 376 | NOP | - | - | - |
| 377 | NOP | - | - | - |
| 378 | NOP | - | - | - |
| 379 | NOP | - | - | - |
| 380 | EFX Bitcrusher depth | EFX | EFX | ? |
| 381 | NOP | - | - | - |
| 382 | NOP | - | - | - |
| 383 | NOP | - | - | - |
| 384 | NOP | - | - | - |
| 385 | NOP | - | - | - |
| 386 | NOP | - | - | - |
| 387 | NOP | - | - | - |
| 388 | NOP | - | - | - |
| 389 | NOP | - | - | - |
| 390 | EFX Reverb dry | EFX | Reverb | ? |
| 391 | EFX Reverb wet | EFX | Reverb | ? |
| 392 | EFX Reverb mode | EFX | Reverb | ? |
| 393 | EFX Reverb decay | EFX | Reverb | ? |
| 394 | EFX Reverb damp | EFX | Reverb | ? |
| 395 | EFX Reverb D0 | EFX | Reverb | - |
| 396 | EFX Reverb D1 | EFX | Reverb | - |
| 397 | EFX Reverb D2 | EFX | Reverb | - |
| 398 | NOP | - | - | - |
| 399 | NOP | - | - | - |
| 400 | NOP | - | - | - |
| 401 | NOP | - | - | - |
| 402 | NOP | - | - | - |
| 403 | NOP | - | - | - |
| 404 | NOP | - | - | - |
| 405 | NOP | - | - | - |
| 406 | NOP | - | - | - |
| 407 | NOP | - | - | - |
| 408 | NOP | - | - | - |
| 409 | NOP | - | - | - |
| 410 | EFX Routing | EFX | EFX | ? |
| 411 | Output level | Master | Volume | *Output dial* |
| 412 | Gain | Master | Volume | *Output dial* |
| 413 | NOP | - | - | - |
| 414 | NOP | - | - | - |
| 415 | NOP | - | - | - |
| 416 | NOP | - | - | - |
| 417 | NOP | - | - | - |
| 418 | NOP | - | - | - |
| 419 | NOP | - | - | - |
| 420 | Control 1 max | ? | ? | ? |
| 421 | Control 1 min | ? | ? | ? |
| 422 | Control 2 max | ? | ? | ? |
| 423 | Control 2 min | ? | ? | ? |
| 424 | Control 3 max | ? | ? | ? |
| 425 | Control 3 min | ? | ? | ? |
| 426 | Control 4 max | ? | ? | ? |
| 427 | Control 4 min | ? | ? | ? |
| 428 | NOP | - | - | - |
| 429 | NOP | - | - | - |
| 430 | NOP | - | - | - |
| 431 | NOP | - | - | - |
| 432 | NOP | - | - | - |
| 433 | NOP | - | - | - |
| 434 | NOP | - | - | - |
| 435 | NOP | - | - | - |
| 436 | NOP | - | - | - |
| 437 | NOP | - | - | - |
| 438 | NOP | - | - | - |
| 439 | NOP | - | - | - |
| 440 | NOP | - | - | - |
| 441 | NOP | - | - | - |
| 442 | NOP | - | - | - |
| 443 | NOP | - | - | - |
| 444 | NOP | - | - | - |
| 445 | NOP | - | - | - |
| 446 | NOP | - | - | - |
| 447 | NOP | - | - | - |
| 448 | NOP | - | - | - |
| 449 | NOP | - | - | - |
| 450 | Arp mode | ? | ? | ? |
| 451 | Arp tempo | ? | ? | ? |
| 452 | Arp tempo fine | ? | ? | ? |
| 453 | Arp division | ? | ? | ? |
| 454 | Arp octaves | ? | ? | ? |
| 455+ | NOP | - | - | - |

Parameters 455-511 are not in use.
