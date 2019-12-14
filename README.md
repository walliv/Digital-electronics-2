
[![university](https://img.shields.io/badge/university-Brno%20University%20of%20Technology-red.svg)](https://www.vutbr.cz/en/)
[![faculty](https://img.shields.io/badge/faculty-Faculty%20of%20Electrical%20Engineering%20and%20Communication-blue.svg)](https://www.fekt.vutbr.cz/)

# AVR Template

## Table of Contents

1. [Introduction](#introduction)
2. [Hardware Components](#hardware-components)
3. [How to Use AVR Template on Linux](docs/HOWTO_linux.md)
4. [How to Use AVR Template on Windows](docs/HOWTO_windows.md)
5. [How to Use AVR Template on Mac OS X](docs/HOWTO_mac.md)
6. [References](#references)


## Introduction

The repository contains all lecture tasks for bachelor course *Digital Electronics 2* ([Winter 2019/2020](https://www.vutbr.cz/en/students/courses/detail/210896)) at Brno University of Technology, Czech Republic. The repository has the following hierarchy:

```bash
avr-template$ tree
.
├── docs
│   ├── ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf
│   ├── dht12_manual.pdf
│   ├── ds3231_manual.pdf
│   ├── esp8266_at_instruction_set.pdf
│   ├── git-cheatsheet.pdf
│   ├── HOWTO_linux.md
│   ├── HOWTO_mac.md
│   ├── HOWTO_windows.md
│   └── hw
│       ├── arduino_shield.kicad_pcb
│       ├── arduino_shield.pdf
│       ├── arduino_shield.pro
│       ├── arduino_shield.sch
│       ├── LCD_tlacitka.sch
│       ├── led_7segment_.sch
│       ├── mcu_modul.sch
│       └── pcb_outline_drawings.sch
├── LICENSE
├── projects
│   ├── library
│   │   ├── inc
│   │   │   ├── gpio.h
│   │   │   ├── lcd_definitions.h
│   │   │   ├── lcd.h
│   │   │   ├── segment.h
│   │   │   ├── timer.h
│   │   │   ├── twi.h
│   │   │   └── uart.h
│   │   └── src
│   │       ├── gpio.c
│   │       ├── lcd.c
│   │       ├── segment.c
│   │       ├── timer.c
│   │       ├── twi.c
│   │       └── uart.c
│   ├── projects.in
│   ├── schprj
│   │   ├── main.c
│   │   ├── Makefile
│   │   └── README.md
│   ├── 01-demo
│   │   ├── main.c
│   │   ├── Makefile
│   │   ├── Makefile.win
│   │   └── README.md
│   ├── 02-leds
│   │   ├── main.c
│   │   └── Makefile
│   ├── 03-gpio
│   │   ├── main.c
│   │   └── Makefile
│   ├── 04-interrupts
│   │   ├── main.c
│   │   └── Makefile
│   ├── 05-segment
│   │   ├── main.c
│   │   └── Makefile
│   ├── 06-lcd
│   │   ├── main.c
│   │   └── Makefile
│   ├── 07-uart
│   │   ├── main.c
│   │   └── Makefile
│   ├── 08-twi_scan
│   │   ├── main.c
│   │   └── Makefile
│   ├── 08-twi_temperature
│   │   ├── main.c
│   │   └── Makefile
│   ├── 09-asm_random
│   │   ├── DEMO.lss
│   │   ├── main.c
│   │   ├── Makefile
│   │   └── rand.S
│   └── 09-burst
│       ├── main.c
│       ├── Makefile
│       └── rand.S
└── README.md
```

In folder `docs` all manuals and datasheets are stored. Folder `hw` contains KiCad schematic of Arduino shields used in the course. All projects are located within `projects` folder. Source and header files of LCD, TWI, segment display and UART libraries are located in the `library` folder.

Breif description of what project folders deal with.

| **Foler Name** | **Description** |
| -------------- | --------------- |
| 01-demo | Default C-code source file
| 02-leds | Controls led blinking
| 03-gpio | Basic funcitons for I/O port setting
| 04-interrupts | Led blinking using timer overflow interrupt
| 05-segment | Controlling 7 segment display using segment.c library
| 06-lcd | Provides code for two row LCD display and making custom characters
| 07-uart | Send information via UART (USB) to computer
| 08-twi_scan | Using I2C bus to find devices
| 08-twi_temperature | Attempt to receive data from I2C bus
| 09-asm_random | Random number generator using LSFR written in Assembly language
| 09-burst | Attempt of burst generator in Assembly language
| schprj | Controlling two servos using analog joystick (semestral project)

## Hardware Components

The following hardware components are mainly used in the lab.

| **Component** | **Description** | **Manual** |
| ------------- | --------------- | ---------- |
| [ATmega328P](https://www.microchip.com/wwwproducts/en/ATmega328P) | 8-bit microcontroller | [Instruction set](https://www.microchip.com/webdoc/avrassembler/avrassembler.wb_instruction_list.html)
| [Arduino Uno board](https://arduino-shop.cz/arduino/1353-klon-arduino-uno-r3-atmega328p-ch340-mini-usb-1466635561.html) | Low-cost clone of Arduino UNO R3 CH340 mini USB | [Schematic](docs/hw/arduino_shield.pdf)
| [Breadboard](https://www.gme.cz/nepajive-kontaktni-pole-zy-60) | 300-pin breadboard |
| [Male-male wires](https://arduino-shop.cz/arduino/1063-arduino-vodice-samec-samec-40-kusu-1500635966.html) | Wires for interconnections |
| [Logic analyzer](https://www.ebay.com/sch/i.html?LH_CAds=&_ex_kw=&_fpos=&_fspt=1&_mPrRngCbx=1&_nkw=24mhz%20logic%20analyzer&_sacat=&_sadis=&_sop=12&_udhi=&_udlo=) | 24MHz 8-channel logic analyzer | [Software](https://www.saleae.com/)
| [Multi-function shield](https://www.gme.cz/experiment-shield-pro-arduino) | Multi-function shield with four LEDs, three push buttons, four seven-segment displays, and others | [Schematic](docs/hw/arduino_shield.pdf)
| [Arduino LCD Shield](https://arduino-shop.cz/en/arduino-platform/899-arduino-lcd-shield-1420670167.html) | LCD and keypad shield with LCD and five push buttons | [Schematic](docs/hw/arduino_shield.pdf)
| [DHT12](https://arduino-shop.cz/arduino/1977-i2c-teplomer-a-vlhkomer-dht12-digitalni.html) | I2C humidity and temperature sensor | [Data sheet](docs/dht12_manual.pdf)
| [DS3231](https://arduino-shop.cz/hledani.php?q=DS3231&n_q=) | I2C real time clock | [Data sheet](docs/ds3231_manual.pdf)
| [ESP8266](https://arduino-shop.cz/arduino/911-internet-veci-je-tady-tcp-ip-wifi-esp8266-1420990568.html) | Wi-Fi module | [AT commands](docs/esp8266_at_instruction_set.pdf)
| [Joystick PS2](https://arduino-shop.cz/arduino/884-arduino-joystick-ps2.html) | Analog Joystick HW-504 |
| [Micro servo](https://arduino-shop.cz/arduino/897-arduino-servo-motor.html) | Micro servo SG90 | [Datasheet](https://components101.com/sites/default/files/component_datasheet/SG90%20Servo%20Motor%20Datasheet.pdf)

## References

1. [Git, free and open source distributed version control system](https://git-scm.com/)
2. [GNU Make tool for Linux](https://www.gnu.org/software/make/)
3. [Minimalist GNU for Windows](http://www.mingw.org/wiki/Getting_Started/)
4. [AVRDUDE, software for programming Atmel AVR Microcontrollers](http://savannah.nongnu.org/projects/avrdude/)
5. Microchip, [AVR 8-bit Toolchain for Windows, Linux, Mac OS X](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains-c-compilers)
6. [Atom text editor](https://atom.io/)
7. [Doxygen, a standard tool for generating documentation from annotated source files](http://doxygen.nl/)
8. [Graphviz, open source graph visualization software](http://graphviz.org/)
9. Peter Fleury, [AVR-GCC libraries](http://homepage.hispeed.ch/peterfleury/avr-software.html)
10. Wykys, [Tools for development of AVR microcontrollers](https://github.com/wykys/AVR-tools)

## Tested on Operating Systems

**Name**   | **Version**                | **Result**      | **Note**
---------- | -------------------------- | --------------- | --------
OpenSUSE   | 15.1, Leap                 | OK (2019-11-27) | Home
Linux Mint | 18.3, Sylvia               | OK (2019-06-13) | Laptop
Windows    | Windows 7                  | OK (2019-05-17) | Lab
Linux Mint | 18.2, Sonya                | OK (2019-05-17) | Lab
Ubuntu     | 18.04.1 LTS, Bionic Beaver | OK (2019-05-15) | Office
Ubuntu     | 16.04, Xenial Xerus        | OK (2018-09-15) | Office

```bash
# FYI: How to check OS version in Linux
cat /etc/os-release
```
