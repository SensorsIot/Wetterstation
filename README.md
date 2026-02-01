<p align="center">
  <h1 align="center">🌤️ ESP32 Wetterstation</h1>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white" alt="ESP32"/>
  <img src="https://img.shields.io/badge/PlatformIO-F5822A?style=for-the-badge&logo=platformio&logoColor=white" alt="PlatformIO"/>
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++"/>
  <img src="https://img.shields.io/badge/FreeRTOS-78C557?style=for-the-badge&logo=freertos&logoColor=white" alt="FreeRTOS"/>
  <img src="https://img.shields.io/badge/License-MIT-blue?style=for-the-badge" alt="License"/>
</p>

<p align="center">
  Eine Wetterstation mit ESP32, BME280-Sensor und OLED-Display.<br/>
  Messwerte auf dem Display <strong>und</strong> über ein Captive Portal als Web-Interface.
</p>

---

## ✨ Features

| Feature | Beschreibung |
|---------|-------------|
| 🌡️ **Temperatur** | BME280 Messung in °C |
| 💧 **Luftfeuchtigkeit** | Relative Feuchte in %RH |
| 🎈 **Luftdruck** | Barometrischer Druck in hPa |
| 📺 **OLED-Display** | Live-Anzeige auf 128×64 SSD1306 |
| 🌐 **Web-Interface** | Captive Portal mit Auto-Update (2s) |
| 📡 **Wi-Fi AP** | SSID: `Wetterstation` (offen, kein Passwort) |
| 🔄 **OTA-Updates** | Firmware kabellos aktualisieren |
| ⚡ **FreeRTOS** | Parallele Tasks für Sensor, Display & OTA |

---

## 🛠️ Hardware

| Komponente | Typ |
|-----------|-----|
| **Mikrocontroller** | ESP32 DevKit V1 |
| **Sensor** | BME280 (I2C, `0x76`) |
| **Display** | SSD1306 OLED 128×64 (I2C, `0x3C`) |

### 🔌 Verdrahtung

```
ESP32          BME280 / SSD1306
─────          ─────────────────
3.3V    ───►   VIN / VCC
GND     ───►   GND / GND
GPIO 21 ───►   SDA / SDA
GPIO 22 ───►   SCL / SCL
```

---

## 📁 Projektstruktur

```
src/
├── config.h          # 📋 Pins, Adressen, Konstanten
├── sensor.h/.cpp     # 🌡️ BME280 auslesen (Thread-sicher)
├── display.h/.cpp    # 📺 OLED-Anzeige
├── webserver.h/.cpp  # 🌐 Captive Portal & HTML-Interface
├── ota.h/.cpp        # 🔄 OTA-Update Support
└── main.cpp          # 🚀 Setup & RTOS Tasks
```

---

## 🚀 Build & Upload

> **Voraussetzung:** [PlatformIO CLI](https://platformio.org/) installiert

```bash
# 🔌 Erster Upload via USB
pio run -e esp32dev -t upload

# 📡 Spätere Updates via OTA (kabellos)
pio run -e esp32dev_ota -t upload
```

---

## 📱 Benutzung

1. ⚡ ESP32 mit Strom versorgen
2. 📶 Mit WLAN **`Wetterstation`** verbinden (kein Passwort)
3. 🌐 Browser öffnet automatisch die Seite — oder manuell **`192.168.4.1`**

---

## 📜 Lizenz

MIT
