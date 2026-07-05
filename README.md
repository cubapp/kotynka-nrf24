# NRF24 Long-Range Temperature Monitor

Wireless DS18B20 temperature sender (every 60s) using E01-2G4M27D + Arduino Nano. Receiver forwards data via USB to Raspberry Pi.

## Features
- Long range (E01-2G4M27D + 7dBi antenna)
- Daily automatic restart via watchdog
- RGB status LEDs
- Simple integer output to `actual_temperature.txt`

## Hardware
- 2× Arduino Nano CH340
- 2× E01-2G4M27D + NRF24 adapter
- DS18B20 waterproof
- NiceRF 7dBi antenna

## Wiring

(See `hardware/` folder or detailed table in the project.)

**Sender pins**: DS18B20 → D2, NRF24 CE→D9, CSN→D10, RGB → D5/D6/D7

**Receiver**: Same NRF24, RGB → D5/D6/D7

## Installation

1. Install Arduino IDE + RF24, OneWire, DallasTemperature libraries
2. Flash `sender.ino` and `receiver.ino`
3. Connect receiver via USB to Raspberry Pi (`/dev/ttyUSB0`)

## Raspberry Pi Python Script

```python
import serial, time
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
while True:
    line = ser.readline().decode().strip()
    if line:
        with open('actual_temperature.txt', 'w') as f:
            f.write(line)
