## Board Wemos D1

A mini wifi board with 4MB flash based on ESP-8266EX.
In stck we have the v3.0.0.

### Specifications

* 11 digital IO, interrupt/pwm/I2C/one-wire supported(except D0)
* Micro USB connexion.
* 1 analog input(3.2V max input)

| Specification     | value       |
|:------------------|:------------|
| Operating Voltage | 3.3V        |
| Digital I/O       | 11          |
| Analog Input Pins | 1(3.2V Max) |
| Clock Speed       | 80/160MHz   |
| Flash             | 4M Bytes    |
| Size              | 34.2*25.6mm |
| Weight            | 3g          |

[Schematics](datasheets/d1_mini_v3.0.0.pdf)

### Wiring

All pins runs at 3.3V

![](images/WemosD1_wiring.png)

| Pin  | Function                     | ESP-8266 Pin |
|:-----|:-----------------------------|:-------------|
| TX   | TXD                          | TXD          |
| RX   | RXD                          | RXD          |
| A0   | Analog input, max 3.2V       | A0           |
| D0   | IO                           | GPIO16       |
| D1   | IO, SCL                      | GPIO5        |
| D2   | IO, SDA                      | GPIO4        |
| D3   | IO, 10k Pull-up              | GPIO0        |
| D4   | IO, 10k Pull-up, BUILTIN_LED | GPIO2        |
| D5   | IO, SCK                      | GPIO14       |
| D6   | IO, MISO                     | GPIO12       |
| D7   | IO, MOSI                     | GPIO13       |
| D8   | IO, 10k Pull-down, SS        | GPIO15       |
| G    | Ground                       | GND          |
| 5V   | 5V                           | -            |
| 3V3  | 3.3V                         | 3.3V         |
| RST  | Reset                        | RST          |
