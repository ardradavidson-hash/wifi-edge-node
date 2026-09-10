# WiFi Edge Node

An ESP32-based Wi-Fi edge node for environmental monitoring in a polyhouse environment. The node is designed to collect sensor data locally and provide wireless connectivity for future monitoring and data-processing stages.

## Day 1: Hardware Setup and Repository Initialization

### Objectives

* Set up and verify the ESP32 development board.
* Flash and test a basic Blink firmware.
* Verify serial communication and identify the microcontroller.
* Compare ESP32 and ESP8266 as possible edge-node platforms.
* Select suitable GPIO pins for future sensor integration.
* Document the DHT22 interface for the Day 5 sensor connection.
* Establish a structured firmware repository.

---

## 1. Hardware Platform Selection

The selected microcontroller for the edge node is the **ESP32**.

Both the ESP32 and ESP8266 are low-cost Wi-Fi-enabled microcontrollers suitable for IoT and edge-monitoring applications. The ESP32 was selected because it provides greater processing capability, more GPIO and peripheral options, and better scope for future expansion.

### ESP32 vs ESP8266

| Feature               | ESP32                               | ESP8266                                   |
| --------------------- | ----------------------------------- | ----------------------------------------- |
| CPU                   | Dual-core Xtensa LX6, up to 240 MHz | Single-core Tensilica L106, up to 160 MHz |
| Wi-Fi                 | 2.4 GHz 802.11 b/g/n                | 2.4 GHz 802.11 b/g/n                      |
| Bluetooth             | Bluetooth Classic + BLE             | Not available                             |
| GPIO availability     | Higher                              | Lower                                     |
| ADC                   | Multiple ADC channels               | Limited ADC capability                    |
| Peripherals           | UART, SPI, I2C, PWM, ADC, etc.      | UART, SPI, I2C, PWM, ADC, etc.            |
| Processing capability | Higher                              | Lower                                     |
| Expansion potential   | High                                | Moderate                                  |

### Why ESP32 was selected

**Higher processing capability:**
The ESP32 provides a dual-core processor with a clock frequency of up to 240 MHz, providing additional processing capacity for sensor acquisition, communication, and future edge-processing tasks.

**Greater GPIO and peripheral flexibility:**
The ESP32 provides a larger selection of GPIOs and hardware peripherals, which is useful when additional environmental sensors or interfaces are added.

**Bluetooth/BLE support:**
The ESP32 includes Bluetooth Classic and Bluetooth Low Energy. Although Bluetooth is not required for the current node, it provides an additional communication interface for future expansion.

**Better expansion potential:**
The current system initially uses a DHT22 for temperature and humidity measurement. Additional sensors and peripherals can be integrated later without changing the microcontroller platform.

**Suitable for an edge node:**
The combination of Wi-Fi connectivity, processing capability, GPIO availability, ADC support, and multiple communication interfaces makes the ESP32 suitable for the planned polyhouse environmental monitoring node.

---

## 2. ESP32 GPIO Considerations

Not all ESP32 GPIOs are interchangeable. Some pins have special functions during boot, while others are connected internally to the flash memory.

For external sensors, general-purpose GPIOs are preferred to avoid boot-time conflicts and hardware limitations.

### Strapping / boot-related pins

The following pins have boot-strapping functions on the classic ESP32:

* GPIO 0
* GPIO 2
* GPIO 5
* GPIO 12
* GPIO 15

The state of these pins during reset can affect the ESP32 boot configuration. Therefore, they are avoided for the DHT22 data connection.

### Flash-connected GPIOs

GPIO 6 to GPIO 11 are normally connected internally to the ESP32's SPI flash memory and should not be used for external sensors or peripherals.

### Other considerations

* GPIO 34 to GPIO 39 are input-only.
* GPIO 34 to GPIO 39 do not provide the same internal pull-up/pull-down functionality available on many general-purpose GPIOs.
* GPIO 1 and GPIO 3 are commonly used by UART0 for programming and serial communication and are therefore left available for debugging.

---

## 3. ESP32 Pinout

The ESP32 development board provides GPIO pins for digital I/O, analog input, PWM, UART, SPI, I2C, and other peripheral functions.

For this project, GPIO selection prioritizes:

* General-purpose functionality
* Compatibility with digital sensors
* Avoidance of boot-strapping pins
* Avoidance of flash-connected pins
* Availability for future expansion

The onboard LED uses **GPIO 2** on the selected development board. GPIO 2 is a strapping pin, so it is used only for the onboard LED test and is not selected for the DHT22.

---

## 4. DHT22 Sensor

The **DHT22** is a digital temperature and relative-humidity sensor suitable for environmental monitoring.

It provides:

* Temperature measurement
* Relative humidity measurement
* Digital sensor communication through a single data line

For this project, the DHT22 will be powered from the ESP32's **3.3 V supply**.

---

## 5. DHT22 Pin Mapping

A standard bare DHT22 sensor has four pins:

| DHT22 Pin | Function | ESP32 Connection |
| --------- | -------- | ---------------- |
| Pin 1     | VCC      | 3.3 V            |
| Pin 2     | DATA     | GPIO 4           |
| Pin 3     | NC       | Not connected    |
| Pin 4     | GND      | GND              |

### Connection

```text
ESP32                 DHT22

3.3V  ─────────────── VCC
GPIO 4 ────────────── DATA
GND   ─────────────── GND
                      NC ── Not connected


## 6. DHT22 Data Pin Selection

**GPIO 4** has been selected as the DHT22 data pin.

GPIO 4 is a suitable general-purpose GPIO for digital sensor communication and avoids the ESP32 pins reserved for flash operation and the commonly used boot-strapping pins.

The planned connection is therefore:

```text
DHT22 VCC   → ESP32 3.3 V
DHT22 DATA  → ESP32 GPIO 4
DHT22 GND   → ESP32 GND
```

GPIO 4 is reserved as the planned DHT22 interface for the initial sensor integration.

---

## 7. Day 1 Blink Test

The onboard LED was used to verify that the ESP32 could be programmed successfully and execute firmware.

The selected development board uses:

```text
LED_BUILTIN → GPIO 2
```

### Blink firmware

```cpp
#define LED_BUILTIN 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
```

The onboard LED was successfully programmed to blink at one-second intervals.

> Note: GPIO 2 is a boot-strapping pin on the classic ESP32. It is used here because it is connected to the onboard LED on the selected development board and is not used for the external DHT22 sensor.

---

## 8. Serial Board Identification

Serial communication was tested at:

```text
115200 baud
```

The firmware reports information about the ESP32, including:

* Chip model
* Chip revision
* Number of CPU cores
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

The heartbeat message confirms that the firmware continues executing after the board information is printed.

---




The ESP32 is therefore established as the base hardware platform for the Wi-Fi edge node, with GPIO 4 reserved as the planned DHT22 data interface.

