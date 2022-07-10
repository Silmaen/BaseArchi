# Template PlatformIO project

Template for many Arduino-based projects that allow some abstraction 
regarding hardware.

## Requirement

System's requirement:
 * [platformio](https://platformio.org/) >= 6.0.0
 * [gcovr](https://gcovr.com) >= 5.1
 * [doxygen](https://doxygen.nl/) >= 1.9.3

## The Silmaen Base System

A library at the core of the template. This contains all the abstractions required.

## Protocols

### Hardware serial protocols

 * I2C
 * SPI
 * UART

## Compatible Boards

This library is only compatible with the bords I have in stock.

 * Atmel AVR series
   * [Arduino MEGA 2560](doc/BoardArduinoMega.md)
   * [Arduino micro](doc/BoardArduinoMicro.md)
 * Atmel SAM series
   * [Arduino MKR Wifi](doc/BoardArduinoMKRWifi.md)
 * Espressif ESP8266 Series
   * [Wemos D1 Mini](doc/BoardWemosD1.md)

## Compatible Devices

 * Commercial boards
   * Adafruit 10 dof
   * Adafruit MicroSD Breakout
   * Adafruit Ultimate GPS v3
   * [BME280](doc/DeviceBME280.md)
   * Chronodot v2.1
   * nRF24L01+
   * Seeeduino light sensor
 * Commercial shield
   * MKR Env (for Arduino MKR boards)
 * Home-made devices
   * LED display

