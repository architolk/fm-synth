# fm-synth
An FM synth based on XFM2 (sounds) and Teensy (operation)

Goal of this project:
- Use an XFM2 for sound creation
- Interact via serial communication between the XFM2 and a teensy (4.0)
- Use the Teensy to drive seven OLED displays for displaying all information about the synthesizer
- Use the Teensy to monitor 9 rotary encoders (that also include a push button)
- Use the Teensy to drive a lot of LED's (42 in total)
- Use the Teensy to monitor a lot of push buttons (also 42)

We use a lot of multiplexer to get this done:
- A TCA9548A to multiplex the different OLED displays (all displays use 3C as I2C address...)
- A MAX7219CNG to drive a max total of 64 LED's
- Two MCP23017 to monitor the rotary encoders (2 ports for the encoder, 1 port for the button). These MCP23017 will create an interupt after which you can read the level of a particular encoder

Step 1:
- Getting a connection between the Teensy and the OLED display
