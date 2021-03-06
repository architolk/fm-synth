# OSC Oscillator menu

| Blue | 6 (Out) | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) |
|------|---------|---------|---------|---------|---------|---------|---------|
| 0 | Volume | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Wave 1 | Wave 1 |
| 1 | Volume | Ratio/Mode | Ratio/Mode | Ratio/Mode | Ratio/Mode | Ratio/Mode | Ratio/Mode |
| 2 | Volume | Wave 2 | Wave 2 | Wave 2 | Wave 2 | Wave 2 | Wave 2 |
| 3 | Volume | Phase+sync | Phase+sync | Phase+sync | Phase+sync | Phase+sync | Phase+sync |
| 4 | R0 (delay) | R1 (attack) | R2 (decay-1) | R3 (decay-2) | L2 & L3 (sustain) | R4 (release-1) | R5 (release-2) |
| 5 | L0 (delay) | L1 (attack) | L2 (decay-1) | L3 (decay-2) | L3 (sustain) | L4 (release-1) | L5 (release-2) |

The sustain dial in Blue-4 (duration mode) will change both L2 and L3 values.

Parameter value mapping:

| Blue | 6 (Out) | 0 (Op1) | 1 (Op2) | 2 (Op3) | 3 (Op4) | 4 (Op5) | 5 (Op6) |
|------|---------|---------|---------|---------|---------|---------|---------|
| 0 | 180 | 236 | 237 | 238 | 239 | 240 | 241 |
| 1 | 180 | 280/274 | 281/275 | 282/276 | 283/277 | 284/278 | 285/279 |
| 2 | 180 | 268 | 269 | 270 | 271 | 272 | 273 |
| 3 | 180 | 286/13 | 287/13 | 288/13 | 289/13 | 290/13 | 291/13 |
| 4 | 206 | 134 | 135 | 136 | 131 & 132 | 137 | 208 |
| 5 | 205 | 130 | 131 | 132 | 132 | 133 | 207 |

## Volume & Pitch (waves oscillator #1 & #2)

![](../media/OSC-Waves.png)

## Ratio

![](../media/OSC-Ratio.png)

## Feedback (oscillator phase)

![](../media/OSC-Phase.png)

## Duration & Level (pitch envelope)

![](../media/OSC-Envelope.png)

In envelope mode, the dials do not correspond to a particular operator, but to a particular phase of the envelope:
- Output dial: delay phase;
- Operator 1 dial: attack phase (L1/R1);
- Operator 2 dial: decay-1 phase (L2/R2);
- Operator 3 dial: decay-2 phase (L3/R3);
- Operator 4 dial: sustain phase (L3);
- Operator 5 dial: release-1 phase (L4/R4);
- Operator 6 dial: release-2 phase (L5/R5).

You select the particular operator, by pressing the corresponding dial. This is made visible on the bottom screen.

When you click on the output-dial, you enter "rate" mode and in this mode, you can change the rate values for any of the operator envelopes. You can change the rate for all operators at the same time, by turning the output-dial.

![](Envelope.png)

In **Duration** mode, sustain acts as a "normal" ADSR sustain level, so not only L3 is affected, but also L2 (end of Decay-1 level). With settings L0=L4=L5=0 and L1=255, you get a "normal" ADSR. Attack sets the attack rate, decay-1 sets the decay rate and release-1 sets the release rate.

Two duration modes are available:
- ADDSRR: "normal" operation, rates for decay and release can be set independently.
- ADDS: "plucked" operation, rates for decay and release are matched. In this mode, you can quickly create plucked envelopes (the rate change of the sound after the attack phase matches the rate change of the sound after key release).

In **Level** mode, all dials correspond to the end level of that phase. Because the end level of decay-2 is the same as the end level of sustain, these dials respond to the same parameter, L3.
