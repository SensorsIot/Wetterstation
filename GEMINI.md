# Projekt: Wetterstation

## Projektübersicht

Dieses Projekt ist eine Wetterstation, die mit einem ESP32 und einem BME280-Sensor realisiert wird. Die Wetterdaten (Temperatur, Luftfeuchtigkeit, Luftdruck) werden auf einem SSD1306 OLED-Display angezeigt.

Das Projekt verwendet FreeRTOS, um die Messung der Sensordaten und die Anzeige auf dem Display in separaten Tasks auszuführen. Dies ermöglicht eine modulare und erweiterbare Softwarearchitektur.

**Hauptkomponenten:**

*   **ESP32:** Mikrocontroller
*   **BME280:** Sensor für Temperatur, Luftfeuchtigkeit und Luftdruck
*   **SSD1306:** OLED-Display

## Build- und Ausführungsprozess

**Benötigte Bibliotheken:**

*   `Adafruit_GFX.h`
*   `Adafruit_SSD1306.h`
*   `Adafruit_BME280.h`
*   `Wire.h`

Diese Bibliotheken müssen in der Arduino IDE installiert werden.

**Vorgehen:**

1.  Öffnen Sie die Datei `Wetterstation/Wetterstation.ino` in der Arduino IDE.
2.  Stellen Sie sicher, dass das richtige Board (ESP32 Dev Module) und der richtige Port ausgewählt sind.
3.  Kompilieren und laden Sie den Sketch auf den ESP32.

## Entwicklungskonventionen

Der Code ist in zwei Haupt-Tasks unterteilt:

*   **`taskMeasure`:** Misst alle 2 Sekunden die Wetterdaten vom BME280-Sensor.
*   **`taskDisplay`:** Aktualisiert das OLED-Display alle 1 Sekunde mit den aktuellen Wetterdaten.

Die beiden Tasks werden über einen Mutex (`i2cMutex`) synchronisiert, um den Zugriff auf den I2C-Bus zu regeln.
