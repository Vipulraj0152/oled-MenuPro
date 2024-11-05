# ESP32 OLED Clock and Menu Interface

An ESP32 project that displays a real-time clock and a Flipper Zero-inspired menu interface on an OLED display. Navigate through options using multiple buttons and a sleek, centered display format.

## Features

- **Bold Clock Display**: Shows the current time in large, bold fonts.
- **Flipper Zero-inspired Menu**: Carousel-style menu with prominent, centered display for each option and smaller, adjacent options.
- **Menu Options**: Switch between options like Main, Menu, Setting, and IP.
- **Auto Return to Clock**: Returns to the clock display if idle for 5 seconds.

## Hardware Requirements

- ESP32 Board
- OLED Display (128x64) with I2C interface
- 5 Push Buttons for navigation
- Jumper Wires

## Wiring

| Button  | ESP32 GPIO Pin |
|---------|----------------|
| Up      | GPIO 12       |
| Down    | GPIO 13       |
| Left    | GPIO 14       |
| Right   | GPIO 27       |
| Enter   | GPIO 26       |

**OLED Display Connections**:
- **VCC** → 3.3V (ESP32)
- **GND** → GND (ESP32)
- **SCL** → GPIO 22 (ESP32)
- **SDA** → GPIO 21 (ESP32)

You can refer to the [wiring diagram](images/wiring_diagram.png) for more details.

## Libraries

Install the following libraries via the Arduino Library Manager:

- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) - For OLED display
- [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library) - For graphics functions
- [TimeLib](https://github.com/PaulStoffregen/Time) - For time handling

## Installation

1. Clone this repository or download the ZIP.
   ```bash
   git clone https://github.com/your-username/ESP32_OLED_Menu_Project.git
   cd ESP32_OLED_Menu_Project/src
