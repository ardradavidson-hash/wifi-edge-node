# ESP32 Blink and Serial Test

## Objective

To verify that the ESP32 development board can be programmed successfully, execute firmware, control its onboard LED, and communicate through the serial monitor.

## Hardware

* ESP32 Development Board
* USB cable
* Computer with Arduino IDE

## Board Configuration

**Board:** ESP32 Dev Module

**LED Pin:** GPIO 2

**Serial Baud Rate:** 115200

## Blink Test

The onboard LED was programmed to switch between HIGH and LOW states at one-second intervals.

```cpp
#define ESP32

#define LED_BUILTIN 2

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("Board: ESP32");

  Serial.printf("Chip model: %s\n", ESP.getChipModel());
  Serial.printf("Chip revision: %d\n", ESP.getChipRevision());
  Serial.printf("Cores: %d\n", ESP.getChipCores());
  Serial.printf("Flash: %u bytes\n", ESP.getFlashChipSize());
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Polyhouse edge node heartbeat");
  delay(500);

  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

```

## Serial Board Identification

The ESP32 was tested using serial communication at 115200 baud.

The firmware reports:

* Board type
* Chip model
* Chip revision
* CPU core count
* Flash memory size

Example output:

```text
================================
       POLYHOUSE EDGE NODE
================================
Board: ESP32
Chip model: ESP32-D0WDQ6
Chip revision: 1
CPU cores: 2
Flash size: 4194304 bytes
================================

Polyhouse edge node heartbeat
```

The `Polyhouse edge node heartbeat` message is printed continuously to confirm that the firmware remains operational after startup.

## Result

| Test                 | Result |
| -------------------- | ------ |
| Firmware upload      | PASS   |
| Onboard LED blink    | PASS   |
| Serial communication | PASS   |
| Board identification | PASS   |

## Note

GPIO 2 is used for the onboard LED on the selected development board. Since GPIO 2 is a boot-strapping pin on the classic ESP32, it is not selected for the external DHT22 sensor.

The planned DHT22 DATA connection is GPIO 4.
