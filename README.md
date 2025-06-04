# Ctrl-IQ-Home

Ctrl IQ Home is a smart home automation project that brings intelligent control, real-time monitoring, and remote access to everyday appliances and environmental sensors. Built on the ESP32 microcontroller, it integrates with Firebase and Blynk App for seamless cloud communication and mobile control.

---

## 🚀 Features

- 🌡️ **Temperature & Humidity Monitoring** using DHT11
- 💡 **Automatic Light Control** with LDR Sensor
- 🛡️ **Proximity Detection** via Ultrasonic Sensor
- 🔌 **Appliance Control** using Relay Module
- 📺 **Real-Time LCD Display** for feedback
- 📷 **Camera Surveillance** using ESP32-CAM
- 📲 **Remote Monitoring and Control** using Blynk App
- ☁️ **Cloud Sync & Storage** with Firebase Realtime Database
- 💡 **Visual Feedback** using LEDs
- 🔁 **Edge-Level Automation** using ESP32 logic

---

## 🛠️ Hardware Used

- ESP32 Dev Board (Wi-Fi)
- ESP32-CAM Module
- DHT11 Temperature and Humidity Sensor
- LDR Sensor
- Ultrasonic Sensor (HC-SR04)
- Relay Module (2/4 Channel)
- 16x2 LCD with I2C Module
- LEDs and Resistors
- Breadboard & Jump Wires
- Power Supply/USB Cable

---

## 📱 Software & Libraries

- **Arduino IDE** (Firmware development)
- **Blynk App** (Mobile interface)
- **Firebase** (Cloud backend)
- **Pandas, Streamlit** (for possible UI/dashboard extensions)
- Arduino Libraries:
  - `DHT`
  - `LiquidCrystal_I2C`
  - `Ultrasonic`
  - `FirebaseESP32`
  - `BlynkSimpleEsp32`

---

## 📐 System Architecture

```mermaid
graph TD
    A[Blynk App]
    B[Wi-Fi + Firebase]
    C[ESP32 Microcontroller]
    D1[Sensors: DHT11, LDR, Ultrasonic]
    D2[Actuators: Relay Module, LEDs]
    D3[Camera: ESP32-CAM]
    D4[Display: 16x2 LCD (I2C)]

    A --> B
    B --> C
    C --> D1
    C --> D2
    C --> D3
    C --> D4


📈 Future Improvements
Add voice control using Google Assistant

Integrate real-time alerts via Telegram or Email

Build advanced web dashboard with Streamlit

Add power usage analytics using current sensors
