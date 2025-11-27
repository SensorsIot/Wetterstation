<p align="center">
  <img src="https://www.arduino.cc/en/uploads/Main/arduino-logo-small.png" alt="Arduino Logo" width="200"/>
</p>

# ESP32 Wetterstation mit BME280

![Lizenz](https://img.shields.io/badge/license-MIT-blue.svg)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![ESP32](https://img.shields.io/badge/ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)

Eine einfache, aber leistungsstarke Wetterstation, die auf einem ESP32 basiert und einen BME280-Sensor zur Messung von Temperatur, Luftfeuchtigkeit und Luftdruck verwendet. Die Daten werden auf einem gestochen scharfen SSD1306 OLED-Display angezeigt.

## ✨ Features

-   🌡️ **Temperaturmessung** in Celsius
-   💧 **Luftfeuchtigkeitsmessung** in %RH
-   🎈 **Luftdruckmessung** in hPa
-   📺 **OLED-Display** zur Anzeige der Daten
-   🤖 **FreeRTOS-basiert** für stabile und parallele Ausführung

## 🛠️ Hardware

| Komponente      | Beschreibung                               |
| --------------- | ------------------------------------------ |
| **ESP32**       | Mikrocontroller mit integriertem WLAN/BT   |
| **BME280**      | Sensor für Temperatur, Feuchtigkeit, Druck |
| **SSD1306**     | 128x64 I2C OLED Display                    |
| **Breadboard**  | Für den einfachen Aufbau                   |
| **Kabel**       | Dupont-Kabel zur Verbindung                |

## ⚙️ Software & Installation

### Benötigte Bibliotheken

Stellen Sie sicher, dass die folgenden Bibliotheken in Ihrer Arduino IDE installiert sind:

-   `Adafruit GFX Library`
-   `Adafruit SSD1306`
-   `Adafruit BME280 Library`

### Einrichtung

1.  **Verkabelung:** Verbinden Sie die Komponenten wie folgt:
    -   **BME280 & SSD1306 an ESP32:**
        -   `SDA` -> `GPIO 21`
        -   `SCL` -> `GPIO 22`
        -   `VCC` -> `3.3V`
        -   `GND` -> `GND`
2.  **Arduino IDE:**
    -   Öffnen Sie `Wetterstation/Wetterstation.ino`.
    -   Wählen Sie das Board "ESP32 Dev Module".
    -   Wählen Sie den korrekten COM-Port.
3.  **Hochladen:** Kompilieren und laden Sie den Sketch auf den ESP32.

## 📁 Code-Struktur

Das Projekt ist zur besseren Übersicht in mehrere Dateien aufgeteilt:

```
Wetterstation/
├── Wetterstation.ino   # Hauptdatei mit setup() und loop()
├── config.h            # Konfigurationen (Pins, Adressen)
├── globals.h           # Globale Variablen und Objekte
└── tasks.h             # RTOS-Tasks für Messung und Anzeige
```

## 📜 Lizenz

Dieses Projekt ist unter der **MIT-Lizenz** lizenziert. Siehe die [LICENSE](LICENSE)-Datei für weitere Details.
