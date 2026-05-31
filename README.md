# ESP32 Environmental Monitor

A battery-powered environmental monitor built with an ESP32 that displays
temperature, humidity, and atmospheric pressure on a compact TFT display.
Press the button to activate the display for 10 seconds.

## Features
- Reads temperature, humidity, and pressure via BME280 sensor
- 0.96" ST7735S TFT color display (80x160)
- Button activated display to conserve battery
- LiPo battery powered (1000mAh)
- Low power design with display backlight control

## Hardware
| Component | Details |
|---|---|
| Microcontroller | SunFounder ESP32 dev board |
| Sensor | BME280 temperature/humidity/pressure |
| Display | 0.96" ST7735S TFT (80x160) |
| Battery | 1000mAh 3.7V LiPo |
| Button | Tactile push button |

## Wiring
| BME280 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| CSB | 3.3V |
| SDO | GND |

| TFT Display | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SCL | GPIO 18 |
| SDA | GPIO 23 |
| RES | GPIO 4 |
| DC  | GPIO 2 |
| CS  | GPIO 5 |
| BLK | GPIO 15 |

| Button | ESP32 |
|---|---|
| Pin 1 | GPIO 13 |
| Pin 2 | GND |

## Libraries Required
- Adafruit BME280 Library
- Adafruit GFX Library
- Adafruit ST7735 and ST7789 Library

Install via Arduino IDE: Sketch → Include Library → Manage Libraries

## How to Run
1. Install Arduino IDE
2. Add ESP32 board support
3. Install required libraries
4. Wire components as shown above
5. Upload src/main.ino to your ESP32
6. Press button to display readings

## Planned Improvements
- Custom PCB with integrated charging circuit
- Solar charging via CN3791 IC
- Deep sleep for extended battery life
- 3D printed enclosure

## License
MIT
