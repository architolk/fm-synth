# Wiring instructions

The wiring could be done from the schematics, but just to be sure: here are some instructions, with photo's!

Buttons to analog input:
- Teensy most left: blue/green wire to panel with red buttons (blue to closest outside of panel)
- Teensy: white/black wire to top of panel with orange buttons (black to closest outside of panel)
- Teensy: purple/white wire to middle of panel with orange buttons (white wire to closest to other connector on same panel)
- Teensy: black/white wire to bottom of panel with orange buttons (black to closest outside of panel)
- Teensy most right red/brown wire to panel with green buttons (red to closest middle of panel)

Screens to Teensy:
- Yellow wire = Vin

Encoders:
(from top - red wires to bottom)
Top pins:
- Most left: blue - green - yellow: to 4th encoder
- Skip one pin
- green: to 5th encoder
- brown - rede - white: to 1th encoder (topmost encoder)

Next row:
- Most left: orange - brown - rede: to 6th encoder
- blue - yellow: to 5th encoder
- blue - purple - white: to 2th encoder

Next row:
- Most left: orange - brown - red: to 7th encoder (bottom encoder)
- skip one pin
- yellow: to 10th encoder (most right encoder)
- green - yellow - orangje: to 3th encoder

Next row:
- Most left: black: to 7th encoder
- black: to 8th encoder
- white - brown - red: to 8th encoder
- white - purple - blue: to 9th encoder
- green - orange: to 10th encoder
