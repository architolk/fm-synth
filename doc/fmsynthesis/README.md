# FM Synthesis explained

## Sources

- https://www.futur3soundz.com/wavetable-synthesis
- https://en.wikipedia.org/wiki/Frequency_modulation_synthesis
- http://www.soundonsound.com/sos/apr00/articles/synthsecrets.htm
- https://www.soundonsound.com/techniques/more-frequency-modulation
- http://ccrma.stanford.edu/software/snd/snd/fm.html
- https://homepages.abdn.ac.uk/d.j.benson/pages/html/music.pdf

## Theory - simple FM (one carrier, one modulator)

Let:
- Fc: the frequency of the carrier
- Fm: the frequency of the modulator
- C: The frequency-ratio of the carrier (we will only use a value of C=1)
- M: The frequency-ratio of the modulator
- I: The modulation index

The "side band order" k=0,1,2,3,..

To compute the actual frequency spectrum, we need to consider the sidebands from the original carrier frequency Fc. The 0th order sideband is the frequency Fc. Sideband orders range from k=0,1,2,3,.. Both left sidebands (frequencies to the left of the carrier frequency) and right sidebands (frequencies to the right of the carrier frequency) occur. The actual frequencies of such a sideband is related to the modulation frequency: Fc ± k*Fm

You only need to calculate the I+2 order sideband, all other sidebands will have negligible amplitudes.

The amplitude of a particular order sideband k is calculated using the Bessel function of the same order k of the modulation index:

Amplitude = BesselJ(k,I)

A sideband corresponds to a frequency, so we get the amplitude for that frequency. But we have some things to consider:
- Sideband at frequency 0 is actually a DC offset, so if such a sideband would occur we can ignore this sideband. This frequency only occurs for M = C / r, with r = 1,2,3,... For M>=C this only occurs at M = C.
- Bessel functions with order above 3 can have negative results, so the calculated amplitude is actually negative.
- Odd sidebands at negative frequency have a phase shift of 180 degrees, so as these sidebands are sinoid curves, this phase shift can also be represented by switching the amplitude sign, mainting the same phase as all other sidebands: negative amplitudes become positive, positive amplitudes become negative.
- Sidebands at negative frequencies are actually sidebands at the same positive frequency, but with another phase shift of 180 degrees: another sign switch.

[This excel spreadsheet](fmsynthesis.xlsx) calculates the correct sideband frequencies and amplitudes for a give carrier frequency, modulation ratio and modulation index (for modulation ratio >= 1).

For better understanding of the frequency of the sideband, it is more intuitive to depict them as a ratio of the carrier frequency: R1=Fc, the carrier frequency, R2 = 2*Fc, etc.

| M | Frequencies | First 8 frequency ratios |
|---|-------------|------------------|
| 1 | Fc(1 ± k) | 1,2,3,4,5,6,7,8 |
| 2 | Fc(1 ± 2k) | 1,3,5,7,9,11,13 |
| 3 | Fc(1 ± 3k) | 1,2,4,5,7,8,10,11 |
| 4 | Fc(1 ± 4k) | 1,3,5,7,9,11,13 |
| 5 | Fc(1 ± 5k) | 1,4,6,9,11,14,16,19 |
| 6 | Fc(1 ± 6k) | 1,5,7,11,13,17,19,23 |
| 7 | Fc(1 ± 7k) | 1,6,8,13,15,20,22,27 |
| 8 | Fc(1 ± 8k) | 1,7,9,15,17,23,25,31 |

Observe that we have already "mirrored" the negative frequencies to positive frequencies, resulting in extra frequency ratios if M is odd and larger than 1.

Some observations:
- Only M=1 will give us all harmonic frequency components
- When M has an even value, only odd harmonic frequency components are available
- M=2 and M=4 have the same possible frequency components (all odd ratio's)
- Higher values of M (from M=4) won't have frequency components between 2 and M-1

### Some observations how M and I change the timbre of the sound

- I = 0 disables the modulation completely (as expected), so M doesn't matter;
- The larger I, the more sidebands have relevant amplitudes
- M = 1 will have all harmonic frequency components (1,2,3,..)
- The larger M, the greater the gap between frequency components (for example: M=2 will only have odd harmonic frequency components: 1,3,5,7)
- The larger M, the higher the frequency with the last relevant amplitude.

This means that we have two ways of obtaining a "higher" tembre:
- Increasing I (more sidebands, so the last relevant one will have a higher frequency);
- Increasing M (larger gap between sideband frequencies, so the last relevant one will have a higher frequency).

### Frequency spectrum analysis

A pure wave (for example 440 Hz) can be displayed in the time domain as a sinoid wave. The same wave can also be displayed in the frequency domain: plotting the frequency bands at which (in)harmonic overtones of the root frequency are displayed. In the examples below both the frequency domain graph and the time domain graphs are displayed.

In FM, the frequency domain graph can be calculated using Bessel functions, as described above. But you can also "calculate" the frequency domain graph from the time domain graph using Fourier transforms. Using Fourier transforms, you could actually "analyse" any available sound and using the results, calculate the appropriate values for carriers and modulators as described in [this article](http://www.javelinart.com/FM_Synthesis_of_Real_Instruments.pdf).

The Matlab script [fourier.m](fourier.m) will create a frequency domain graph from any FM created sound wave with one carrier and one modulator. It also contains the calculation of sideband frequencies and amplitudes, so you can compare the two different ways to achieve the same result. You can use the open source tool GNU Octave (https://octave.org) to execute this script.

## Examples

### Sawtooth-like (M=1, I=1.3)
Fc = 440, Fm = 440, C = 1, M = 1, I = 1.3

`y = sin(x + 1.3 * sin(x))` ([show math](https://www.wolframalpha.com/input/?i=y%3Dsin%28x%2B1.3*sin%28x%29%29))

![](Sidebands_Sawtooth.png)

![](Graph_Sawtooth.png)

![](Wave_Sawtooth.png)

### Square-like (M=2, I=1,3)
Fc = 440, Fm = 440, C = 1, M = 1, I = 1,3

`y = sin(x + 1.3 * sin(2x))` ([show math](https://www.wolframalpha.com/input/?i=y%3Dsin%28x%2B1.3*sin%282x%29%29))

![](Sidebands_Square.png)

![](Graph_Square.png)

![](Wave_Square.png)

### M=1, I=0 (no modulation)
Fc = 440, Fm = 440, C = 1, M = 1, I = 0

![](Sidebands_C1_M1_I0.png)

No sidebands, because I=0

![](Graph_C1_M1_I0.png)

Because I=0, the modulation ratio doesn't matter: only one frequency component at R1 with amplitude 100%.

![](Wave_C1_M1_I0.png)

### M=1, I=1
Fc = 440, Fm = 440, C = 1, M = 1, I = 1

![](Sidebands_C1_M1_I1.png)

Sidebands at 0, ±1, ±2, ±3, ...

![](Graph_C1_M1_I1.png)

Frequency components with amplitude larger than 10% at R1, R2 and R3 (440,880,1320)

![](Wave_C1_M1_I1.png)

### M=1, I=2

Fc = 440, Fm = 440, C = 1, M = 1, I = 2

![](Sidebands_C1_M1_I2.png)

Sidebands at 0, ±1, ±2, ±3, ...

![](Graph_C1_M1_I2.png)

Frequency components with amplitude larger than 10% at R1, R2, R3, R4 (440,880,1320,1760). The frequency component at R1 is depicted in orange: it has a negative amplitude (phase shifted 180 degrees).

![](Wave_C1_M1_I2.png)

### M=1, I=5

Fc = 440, Fm = 440, C = 1, M = 1, I = 5

![](Sidebands_C1_M1_I5.png)

Sidebands at 0, ±1, ±2, ±3, ...

![](Graph_C1_M1_I5.png)

Frequency components with amplitude larger than 10% at R1, R3, R4, R5, R6, R7 (440,1320,1760,2200,2640,3080)

![](Wave_C1_M1_I5.png)

### M=2, I=1
Fc = 440, Fm = 880, C = 1, M = 2, I = 1

![](Sidebands_C1_M2_I1.png)

Sidebands at 0, ±2, ±4, ±6, ...

![](Graph_C1_M2_I1.png)

Frequency components with amplitude larger than 10% at R1, R3 (440,1320)

![](Wave_C1_M2_I1.png)

### M=2, I=2
Fc = 440, Fm = 880, C = 1, M = 2, I = 2

![](Sidebands_C1_M2_I2.png)

Sidebands at 0, ±2, ±4, ±6, ...

![](Graph_C1_M2_I2.png)

Frequency components with amplitude larger than 10% at R1, R3, R5, R7 (440,1320,2200,3080)

![](Wave_C1_M2_I2.png)

### M=2, I=5
Fc = 440, Fm = 880, C = 1, M = 2, I = 5

![](Sidebands_C1_M2_I5.png)

Sidebands at 0, ±2, ±4, ±6, ...

![](Graph_C1_M2_I5.png)

Frequency components with amplitude larger than 10% at R1, R3, R5, R9,R11,R13 (440,1320,2200,3960,4840,5720)

![](Wave_C1_M2_I5.png)

### M=3, I=1
Fc = 440, Fm = 1320, C = 1, M = 3, I = 1

![](Sidebands_C1_M3_I1.png)

Sidebands at 0, ±3, ±6, ±9, ...

![](Graph_C1_M3_I1.png)

Frequency components with amplitude larger than 10% at R1,R2,R3,R4,R5 (440,880,1760,2200,3080)

![](Wave_C1_M3_I1.png)

### M=3, I=2
Fc = 440, Fm = 1320, C = 1, M = 3, I = 2

![](Sidebands_C1_M3_I2.png)

Sidebands at 0, ±3, ±6, ±9, ...

![](Graph_C1_M3_I2.png)

Frequency components with amplitude larger than 10% at R1, R2, R4 (440,880,1760,2200,3080,4400)

![](Wave_C1_M3_I2.png)

### M=3, I=5
Fc = 440, Fm = 1320, C = 1, M = 3, I = 5

![](Sidebands_C1_M3_I5.png)

Sidebands at 0, ±3, ±6, ±9, ...

![](Graph_C1_M3_I5.png)

Frequency components with amplitude larger than 10% at R1, R2, R4, R5, R7 (440, 880, 1760, 2200, 3080)

![](Wave_C1_M3_I5.png)

## Theory - feedback FM

Feedback FM is actually easier to calculate than "simple" FM:

- Only positive sidebands will occur: k = 1,2,3,..
- The amplitude is calculated using the formula: Amplitude = 2 * BesselJ(k,I * k) / (I * k)
- This function won't work for I = 0 (division by zero), but interestingly, the whole function resolved to 0 for k>1 and to 1 for k=1 (as you would expect: just a regular sinoid wave at feedback level zero).

[This excel spreadsheet](fmfeedback.xlsx) calculates the correct sideband frequencies and amplitudes for a give carrier frequency and modulation index (=feedback ratio), for modulation index < 1.3).

Some interesting things can be said about this spreadsheet:
- Because only the first 20 sidebands are calculated, the calculated wave from the sidebands is a bit "blocky" with respect to the real calculated FM wave. With feedback: higher level sideband DO realy add up!
- From around modulation index 1.3, negative frequencies occur at the highest feedback levels. This introduces noise in the calculated FM wave, but not in the sidebands: they still add up nicely (although resulting in a wave with an increasingly lower amplitude).

## Examples

Only the frequency components graph is displayed, the sidebands are always the same as the frequency components.

### I = 0.5
Fc = 440, C = 1, I = 0.5

`y = sin(x + 0.5 * sin(y))` ([show math](https://www.wolframalpha.com/input/?i=y+%3D+sin%28x+%2B+0.5+*+sin%28y%29%29))

![](Graph_F05.png)

![](Wave_F05.png)

### I = 1.0

![](Graph_F10.png)

![](Wave_F10.png)

### I = 1.2

![](Graph_F12.png)

![](Wave_F12.png)

### I = 1.4

![](Graph_F14.png)

![](Wave_F14.png)

The wave above is from the excel and only shows the calculated spots, not a line. The burst of noise is actually the oscillator going very rapidly going between two extreme values, that's why two separate lines are visible. Using Octave, we can plot a graph that depicts a little bit better what is going on (see [feedback.m](feedback.m) for the script).

![](WaveO_F14.png)

The summed wave from the calculated sideband amplitudes look very well-behaved, but is probably very wrong (not resembling the sound that is actually heard).

![](WaveS_F14.png)

The noise burst is the result of the sampling rate of digital synthesizers. It is the reason that Yamaha originally used an averaging filter for the feedback, using not only the previous value, but actually the average between the previous two values, which will make the noise burst disappear. The explanation is mentioned in [this patent](https://patents.google.com/patent/US4249447A/en), as is visible in the graph below, using the same parameters, but with the average filter (see [feedback-filter.m](feedback-filter.m) for the script).

![](WaveO_F14-filter.png)

Interestingly the "pure" math equation results in a graph that is actually "not possible" from a sound perspective (it goes "back in time"):

`y = sin(x + 1.4 * sin(y))` ([show math](https://www.wolframalpha.com/input/?i=y+%3D+sin%28x+%2B+1.4+*+sin%28y%29%29))
