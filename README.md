# arduino-menorah
Arduino-based electric menorah

## Compiling

To build using `make`, install the
[arduino-mk](https://github.com/sudar/Arduino-Makefile) package. I use Ubuntu,
so the import path is relative where files live in the `apt` installation.
Alternatively, one can import it into the Arduino GUI if they desire.

## Hardware

Building the menorah is fairly straightforward, as is shown by the diagram
below. All resistors in the diagram are 100 Ohm. The blue LED is the Shamash.
Since the candles of the menorah are typically placed right to left and lit
left to right, the circuit in the diagram below is oriented so the Shamash is
on the right-hand side of the menorah. Then, when the LEDs light up, they light
up from left to right.

## Configuring

The amount of LEDs can be configured via the blue, green, and yellow wires
connected to `A0`, `A1`, `A2`. The analog inputs are read digitally as GPIO
inputs where the values make a 3-bit number where `A0` is the least significant
bit. To set a bit low, connect its corresponding wire to ground. The number to
set is one less than the amount of LEDs to be lit. To change the number of
lights, first set the enable pin (purple on the diagram) to ground (set the
switch so all lights are off), set the desired number of lights, then flip the
switch to set the enable pin to high. The lights will light up with a small
delay between LEDs, then remain on until the enable pin goes low again or the
Arduino is powered off.

![Arduino menorah circuit setup](https://github.com/domagalski/arduino-menorah/blob/main/menorah.png)
