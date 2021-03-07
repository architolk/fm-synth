# Teensy encoder

We use an encoder with 5 pin:
- Pin A: output 1 (left pin)
- Pin C: common (middle pin)
- Pin B: output 2 (right pin)
- Pin D: switch left
- Pin E: switch right

The switch is a "normal" push button, so we can do the following:
- VCC to pin D
- Pull-down resistor on pin E
- Read value of pin E via digital IN
(je krijgt dan HIGH als er op de button wordt gedrukt)

Kan ook andersom:
- Ground to Pin D
- Pull-up resistor on pin E
- Read value of pin E via digital IN
(je krijgt dan LOW als er op de button wordt gedrukt)

The encoder werkt als volgt:

Hier staat het wel aardig: http://www.bartvenneker.nl/Arduino/index.php?art=0016
- Pin C gaat naar GND
- Pin A naar Digital input 2
- Pin B naar Digital input 3

(inputs 2 en 3 zijn interuptable)

Inmiddels ook een aardige gevonden, die ook debouncing doet in de software: hierdoor geen hardware aanpassingen nodig!

=> Dit kan ik dan later ook gebruiken bij de MCP23017
    -> Die werkt ook met een interupt

Hier staat het goed uitgelegd: https://www.best-microcontroller-projects.com/mcp23017.html

Deze lijkt ook wel aardig, en met een library: https://github.com/blemasle/arduino-mcp23017/blob/master/examples/PortCopyOnInterrupt/PortCopyOnInterrupt.ino
