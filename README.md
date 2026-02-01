# ESP32 Wetterstation

Eine einfache Wetterstation mit ESP32, BME280-Sensor und OLED-Display. Die Messwerte werden auf dem Display angezeigt und ueber ein Captive Portal als Web-Interface bereitgestellt.

## Bauteile

- ESP32 DevKit V1
- BME280 Sensor (I2C, Adresse 0x76)
- SSD1306 OLED-Display 128x64 (I2C, Adresse 0x3C)

## Verdrahtung

| ESP32     | BME280 | SSD1306 |
|-----------|--------|---------|
| 3.3V      | VIN    | VCC     |
| GND       | GND    | GND     |
| GPIO 21   | SDA    | SDA     |
| GPIO 22   | SCL    | SCL     |

## Funktionen

- Temperatur, Luftfeuchtigkeit und Luftdruck alle 2 Sekunden messen
- Anzeige auf OLED-Display
- Serielle Ausgabe der Messwerte
- Wi-Fi Access Point "Wetterstation" (kein Passwort)
- Captive Portal mit Web-Interface auf 192.168.4.1 (Auto-Update alle 2s)
- OTA-Updates (ArduinoOTA)
- FreeRTOS Tasks fuer parallele Ausfuehrung

## Projektstruktur

```
src/
  config.h        - Pins, Adressen, Konstanten
  sensor.h/.cpp   - BME280 auslesen (Thread-sicher)
  display.h/.cpp  - OLED-Anzeige
  webserver.h/.cpp - Captive Portal und HTML-Interface
  ota.h/.cpp      - OTA-Update Support
  main.cpp        - Setup und RTOS Tasks
```

## Build & Upload

Voraussetzung: [PlatformIO](https://platformio.org/)

```bash
# Erster Upload via USB
pio run -e esp32dev -t upload

# Spaetere Updates via OTA
pio run -e esp32dev_ota -t upload
```

## Benutzung

1. ESP32 mit Strom versorgen
2. Mit dem WLAN **"Wetterstation"** verbinden (kein Passwort)
3. Browser oeffnet automatisch die Seite (oder manuell `192.168.4.1`)

## Lizenz

MIT
