# Ctrl-IQ-Home

Ctrl IQ Home is a smart home automation project that brings intelligent control, real-time monitoring, and remote access to everyday appliances and environmental sensors. Built on the ESP32 microcontroller, it integrates with Firebase and Blynk App for seamless cloud communication and mobile control.

---

## 🚀 Features

- 🌡️ **Temperature & Humidity Monitoring** using DHT11
- 💡 **Automatic Light Control** with LDR Sensor
- 🛡️ **Proximity Detection** via Ultrasonic Sensor
- 🔌 **Appliance Control** using Relay Module
- 📲 **Remote Monitoring and Control** using Blynk App
- ☁️ **Cloud Sync & Storage** with Firebase Realtime Database
- 💡 **Visual Feedback** using LEDs
- 🔁 **Edge-Level Automation** using ESP32 logic

---

## 🛠️ Hardware Used

- ESP32 Dev Board (Wi-Fi)
- DHT11 Temperature and Humidity Sensor
- LDR Sensor
- Ultrasonic Sensor (HC-SR04)
- Relay Module (2/4 Channel)
- LEDs and Resistors
- Breadboard & Jump Wires
- Power Supply/USB Cable
- Pump auto-control

---

## 📱 Software & Libraries

- **Arduino IDE** (Firmware development)
- **Blynk App** (Mobile interface)
- **Firebase** (Cloud backend)
- Arduino Libraries:
  - `DHT`
  - `LiquidCrystal_I2C`
  - `Ultrasonic`
  - `FirebaseESP32`
  - `BlynkSimpleEsp32`

---

## 📐 System Architecture

                   +--------------------+
                   |     Blynk App      |
                   | (Mobile Interface) |
                   +---------+----------+
                             |
               +-------------v-------------+
               |     Wi-Fi + Firebase      |
               | (Cloud Communication)     |
               +-------------+-------------+
                             |
                     +-------v--------+
                     |     ESP32      |
                     | (Main MCU Unit)|
                     +--+------+------+--+-------------------------------+
                        |      |         |             |                |
              +---------+   +---+--+   +--+-----+    +----+----+      +----+----+
              | Sensors  |  |Relay |   | Dc Fan |    | Display |      |  LEDs   |
              | DHT11    |  |Module|   |  LEDs  |    | 16x2 LCD|      | Status  |
              | LDR      |  |      |   |  Pump  |    |   (I2C) |      | Lights  |
              |Ultrasonic|  +------+   +--------+    +---------+      +---------+
              +----------+


---

## 📈 Future Improvements
Add voice control using Google Assistant

Integrate real-time alerts via Telegram or Email

Build advanced web dashboard with Streamlit

Add power usage analytics using current sensors
