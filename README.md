📅 MyDS1302 - DS1302 RTC Library for ESP32

A complete Arduino library for the DS1302 RTC module, developed from scratch with a deep understanding of the communication protocol.

🎯 Features

✅ Developed from scratch without external libraries.

✅ Full DS1302 support (time, date, RAM).

✅ Optimized for ESP32.

✅ Minimal and efficient code (< 300 lines).

✅ Ready-to-use examples.

📦 Installation

Method 1: Via Arduino IDE

Download this repository (Code → Download ZIP)
In Arduino IDE: Sketch → Include Library → Add .ZIP Library
Select the downloaded ZIP file

Method 2: Manually

Copy the MyDS1302_Library folder to your Arduino/libraries/ directory

🔌 Wiring
ESP32        DS1302

3.3V    →    VCC

GND     →    GND

GPIO5   →    CE/RST

GPIO22  →    DAT/IO

GPIO21  →    CLK/SCLK
