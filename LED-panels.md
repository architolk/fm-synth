# LED Panels

LED Panel #1 contains the blue LEDs, and the MAX7219CNG and the 74HCT125 ICs.

From panel #1 the connections are made to the other panels (#2 to #6), as depicted in the schema:

![](panel1-schema.png)

We use female-female jumper cables to connect all panels together. 8-pin cables to connect all panels and a 6-pin cable to connect the panel #1 PCB to the Teensy PCB.

## PCBs

PCB panels may not be correct: placement of diodes should be common cathode! At this moment, they are common anode :-). But the switch is bidirectional, so you can just rotate the switches.

### Panel #1

![](panel1-pcb.png)

Some jumper cables are not placed to not cloud the pcb, the dotted lines mark which jumper cables should be placed.

### Panel #2

![](panel2-pcb.png)

The switches are on one side of the PCB, the header is on the other side. The resistors are also on the back.

Soldering the PCB in this order:
1. Solder routing wires on back & front (wires to the headers are on the front, others are on the back!)
2. Solder resistors (and use resistor wire to make routing complete)
3. Plug in switches and solder all connections
4. Finish with the two connection wires that are on the front and connected to the switches

## BOM

For panel #1:

- 1x PCB 12x5 (cut from a 15x9 PCB)
- 1x MAC7219CNG
- 1x 74HCT125
- 1x 24-pin IC socket
- 1x 14-pin IC socket
- 1x JCT power cable
- 1x male header 6 pins (to teensy)
- 1x female-female jumper cable 6 pins (to teensy)
- 5x male header 8 pins (to all other panels)
- 5x female-female jumpber cable 8 pins (to all other panels)
- 6x blue tactle LED button
- 6x 1.5kOhm resistor (9 kOhm total)

For panel #2:

- 1x PCB 10x2.2
- 1x male header 8 pins (from panel #1)
- 5x red tactle LED button
- 1x male header 2 pins (to teensy)
- 5x 2.2kOhm resistor (11 kOhm total)

For panel #3:

- 1x PCB 12x2.2
- 1x male header 8 pins (from panel #1)
- 6x green tactle LED button
- 1x male header 2 pins (to teensy)
- 6x 1.5kOhm resistor (9 kOhm total)

For panel #4:

- 1x PCB 10x4
- 1x male header 8 pins (from panel #1)
- 9x orange tactle LED button
- 1x male header 2 pins (to teensy)
- 9x 1kOhm resistor (9 kOhm total)

For panel #5:

- 1x PCB 6x6
- 1x male header 8 pins (from panel #1)
- 6x orange tactle LED button
- 1x male header 2 pins (to teensy)
- 6x 1.5 kOhm resistor (9 kOhm total)

For panel #6:

- 1x PCB 10x6.1
- 1x male header 8 pins (from panel #1)
- 9x green tactle LED button
- 1x male header 2 pins (to teensy)
- 9x 1 kOhm resistor (9 kOhm total)

Resistor total:
- 1 kOhm: 9+9 = 18
- 1.5 kOhm: 6+6+6 = 18
- 2.2 kOhm: 5
