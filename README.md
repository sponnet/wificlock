# miniclock

A clock based on NodeMCU / ESP8266 and a TM1637 display module

## Usage

1. Power on device
2. Open your mobile phone and connect to the 'miniclock' WiFi network
3. Enter the credentials of your WiFi network
4. The device will fetch the network time and is ready to use

## Hardware 

- TM1637 LED module : https://www.aliexpress.com/item/4-Bits-Digital-Tube-LED-Display-Module-With-Clock-Display-Board-For-Arduino-DIY-four-digital/32387190376.html

- NodeMCU : https://www.aliexpress.com/item/NodeMcu-Lua-WIFI-development-board-based-on-the-ESP8266-Internet-of-things/32443964726.html

## Software setup

Using the Arduino IDE, install following libraries

- NTPClient by Fabrice Weinberg
- TM1736 by Avishay Orpaz
- WifiManager by tzapu

before uploading the ino file to the device.




