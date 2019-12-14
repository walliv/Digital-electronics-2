
# Semestral Project

## Table of Contents

1. [Introduction](#introduction)
2. [Hardware](#hardware)
3. [Software](#software)
4. [References](#references)

## Introduction

This is the final project in the Digital electronics 2 winter course. It demonstrates the control of two servos using analog joystick.

## Hardware

We have used the Arduino Uno board clone for this implementation. Joystick is connected to two ADC channels (ADC0 and ADC1) which seek after change in position. We use the ADC value afterwards to set an impulse length in Fast PWM mode of TimerCounter1. The PWM of each servo is connected to Output Compare pins (OC1A and OC1B). The PWM frequency was set to 50Hz (according to datasheet of the servo). Wiring diagram is provided in `/Digital-electronics-2/docs` folder.

![Schematic](../../docs/Semestral%20project%20wiring%20diagram.jpg?raw=true "Schematic")

## Software

The ADC prescaler was set to 64 and conversion starts every time TimerCounter0 reaches its TOP value (prescaler set also to 64). ADC channel is changed after ADC conversion complete vector is triggered. For control of PWM TimerCounter1 is used. The TOP value of the counter was set by value of ICR1 register (39999) and remains constant all the time. This value and prescaler value 8 determines the frequency of the output PWM signal. This operation is established by setting of WGM13:0 bits in TCCR1A/B registers to 14. In order to accomplish the correct PWM waveform the compare mode of OCCR1A/B register is set to non-inverted. The OCR1A/B values are changed every time (independent on the end of ADC conversion) in the endless loop.
All codes were assembled using Visual Studio Code and AVR Toolchain for Linux.

## References

1. Microchip, [AVR 8-bit Toolchain for Windows, Linux, Mac OS X](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers)
2. Microchip, [ATmega328P](https://www.microchip.com/wwwproducts/en/ATMEGA328P)
3. Wiring diagram, [Reference](../../docs/Semestral%20project%20wiring%20diagram.jpg)
