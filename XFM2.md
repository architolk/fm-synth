# XFM2 board

Het XFM2 board bestaat uit de CMOD-A7-35T breadboard friendly bordje, plus de UDA1334a I2C stereo DAC bordje. Deze wordt aangesloten conform de beschrijving op https://www.futur3soundz.com. Anders dan op die beschrijving, doen we ook nog:

1. Een externe power input mogelijkheid (directe kabeltjes)
2. Stereo audio-out vanaf de DAC naar een dual jack output
3. Een RX/TX serial port mogelijkheid voor verbinding van de Teensy met de XFM2
4. De MIDI-in zit niet op de PBC, maar hiervoor wordt ook een afzonderlijke kabel gemaakt.

Het schema ziet er als volgt uit:

![](XFM2-schema.png)


## PCB

De PCB ziet er als volgt uit. We gebruiken:

- PCB 60x80 mm
- Minimale aantal pins: 19x24

Omdat het PCB aan de bovenkant direct moet beginnen met holes, omdat we zowel de mini-USB als mini-jack willen kunnen gebruiken, moeten we het PCB afsnijden. Hierdoor zijn de verbindingsgaten aan de voorkant niet bruikbaar. De oplossing is om extra gaten te boren:

- Rechtsboven
- Linksmidden (linksvoor kan niet, daar is geen ruimte genoeg)
- Links en rechtsonder

Het PCB kan in principe aan de onderkant ook een stukje korter gemaakt worden, of we gebruiken de gaten die daar al zitten.

![](XFM2-pcb.png)

Merk op dat de "to Power" header feitelijk gewoon de draden zijn naar de powerconnector.

## BOM

- 1x PCB 6x8
- CMOD A7 35T
- UDA1334a
- 24LC1025 memory
- 8 pins IC voetje
- 4N35 optocoupler
- 1N4148 diode
- 220 Ohm resistor
- 470 Ohm resistor
- 1x 2-pin male header
- 1x JST power cable
- 1x dual wire to MIDI out
- 1x triple wire to stereo audio out
