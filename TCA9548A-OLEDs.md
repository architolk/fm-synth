# OLEDs and TCA9548A multiplexer

De OLEDs worden via een TCA9548A multiplexer verbonden met de Teensy. Reden is dat alle OLEDs op hetzelfde I2C adres zitten, dus een enkele bus gaat niet werken.

De TCA9548A heeft 8 afzonderlijke I2C bussen, dus je kunt maximaal 8 OLEDs aansturen.

Onderstaand figuur geeft het schema voor de verbindingen.

![](oleds-schema.png)

Het idee is om alle OLEDs direct op het frontpanel te bevestigen. Vervolgens hebben we twee PCBs (5x7 en 6x8) die female headers hebben waarop de OLEDs aangesloten kunnen worden. Op die manier "klik" je eigenlijk de PCB's op de OLEDs. De twee PCB's worden verbonden met een custom 8x8 female header kabel. Op de grootste PCB zit ook de TCA9548A multiplexer (op de andere kant dan de female headers). Aan deze kant zit ook weer een male header (4 pins), waarmee de TCA9548A verbonden is met de Teensy.

![](oleds-pcb.png)
