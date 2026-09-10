# ESP32 and DHT22 Pin Map

## ESP32 Development Board

The ESP32 is the selected microcontroller for the Wi-Fi edge node. GPIO selection is made considering boot-strapping functions, flash connections, serial communication, and future sensor expansion.

## DHT22 Connection

| DHT22 Pin | Function | ESP32 Connection |
| --------- | -------- | ---------------- |
| Pin 1     | VCC      | 3.3 V            |
| Pin 2     | DATA     | GPIO 4           |
| Pin 3     | NC       | Not connected    |
| Pin 4     | GND      | GND              |

### Connection Summary

```text
DHT22                  ESP32

VCC   ────────────────  3.3 V
DATA  ────────────────  GPIO 4
NC    ────────────────  Not connected
GND   ────────────────  GND
```



## GPIO 4 Selection

GPIO 4 was selected as the DHT22 DATA pin because it is a general-purpose GPIO suitable for digital sensor communication.

The DHT22 connection avoids:

* GPIO 0, 2, 5, 12, and 15, which have boot-strapping functions.
* GPIO 6–11, which are normally connected to the ESP32's internal flash.
* GPIO 1 and 3, which are commonly used for UART0 serial communication.

GPIO 2 is used by the selected development board's onboard LED for the Day 1 Blink test and is therefore not used for the DHT22.

## Planned Connection

```text
ESP32 3.3 V  → DHT22 VCC
ESP32 GPIO 4 → DHT22 DATA
ESP32 GND    → DHT22 GND
```

The DHT22 will be physically connected and tested during the sensor-integration stage.
