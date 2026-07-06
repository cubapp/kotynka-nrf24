# Pinout & Wiring - kotynka-nrf24

## Components
- Arduino Nano (CH340)
- E01-2G4M27D (nRF24L01+ PA+LNA) via adapter board on the 0x000129 channel 
- DS18B20 Waterproof Temperature Sensor
- Common Cathode RGB LED (for status)

---

## Sender Wiring

## Sender (Updated Wiring)

```ascii
Arduino Nano
+-----------------------------------+
|  D2  ─────── Data (Yellow)        | ← DS18B20
|  5V  ─────── VCC (Red)            |
|  GND ─────── GND (Black)          |
|                                   |
|  D5  ─────── CE                   | ← NRF24 Adapter
|  D6  ─────── CSN                  |
|  D11 ─────── MOSI                 |
|  D12 ─────── MISO                 |
|  D13 ─────── SCK                  |
|  3.3V/GND ── VCC/GND              |
|                                   |
|  D7  ─────── Red   (220Ω)         | ← RGB LED (Common Cathode)
|  D8  ─────── Green (220Ω)         |
|  D9  ─────── Blue  (220Ω)         |
|  GND ─────── Common Cathode       |
+-----------------------------------+
```

## Receiver Wiring
``` ascii
Arduino Nano
+-----------------------------------+
|                                   |
|  D9  ─────── CE                   | ← NRF24 Adapter
|  D10 ─────── CSN                  |
|  D11 ─────── MOSI                 |
|  D12 ─────── MISO                 |
|  D13 ─────── SCK                  |
|  3.3V/GND ── VCC/GND              |
|                                   |
|  D5  ─────── Red   (220Ω)         | ← RGB LED (Common Cathode)
|  D6  ─────── Green (220Ω)         |
|  D7  ─────── Blue  (220Ω)         |
|  GND ─────── Common Cathode       |
+-----------------------------------+
```

##Important Notes

*Always use the NRF24 adapter board (it has 3.3V regulator + capacitors).
*Add 47µF capacitor across VCC/GND on the NRF24 adapter for stability.
*Use Old Bootloader version on cheap Nano clones if upload fails.




