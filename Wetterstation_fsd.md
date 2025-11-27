# Funktionale Spezifikation: ESP32 Wetterstation

## 1. Einleitung

### 1.1 Zweck des Dokuments
Dieses Dokument beschreibt die funktionalen und nicht-funktionalen Anforderungen an die ESP32 Wetterstation. Es dient als Referenz für die Entwicklung, Validierung und zukünftige Erweiterungen des Systems.

### 1.2 Umfang
Die Spezifikation deckt die Datenerfassung von Temperatur, Luftfeuchtigkeit und Luftdruck mittels eines BME280-Sensors, die Anzeige dieser Daten auf einem SSD1306 OLED-Display sowie die zugrundeliegende Software-Architektur basierend auf FreeRTOS ab.

### 1.3 Zielgruppe
Dieses Dokument richtet sich an Entwickler, Tester und alle Interessenten, die ein tiefgreifendes Verständnis der Wetterstation erlangen möchten.

## 2. Produktübersicht

### 2.1 Kurze Beschreibung
Die ESP32 Wetterstation ist ein autonomes Gerät, das kontinuierlich Umweltdaten (Temperatur, Luftfeuchtigkeit, Luftdruck) erfasst und diese in Echtzeit auf einem kleinen OLED-Bildschirm anzeigt. Das System ist robust, energieeffizient und nutzt die Vorteile eines Echtzeitbetriebssystems (FreeRTOS) für eine zuverlässige und reaktionsschnelle Leistung.

### 2.2 Ziele und Vision
Das Hauptziel ist die Bereitstellung einer einfach zu bauenden und zu verwendenden Wetterstation, die präzise Messwerte liefert und als Basis für weiterführende IoT-Projekte dienen kann.

## 3. Funktionale Anforderungen

### 3.1 Sensordatenerfassung
*   **FR-1.1:** Das System MUSS Temperaturmesswerte vom BME280-Sensor erfassen.
*   **FR-1.2:** Das System MUSS Luftfeuchtigkeitsmesswerte vom BME280-Sensor erfassen.
*   **FR-1.3:** Das System MUSS Luftdruckmesswerte vom BME280-Sensor erfassen.
*   **FR-1.4:** Die Sensordaten MÜSSEN mindestens alle 2 Sekunden aktualisiert werden.
*   **FR-1.5:** Das System MUSS die Möglichkeit bieten, den I2C-Bus zwischen verschiedenen Tasks sicher zu synchronisieren.

### 3.2 Datenanzeige auf OLED
*   **FR-2.1:** Das System MUSS die aktuelle Temperatur auf dem SSD1306 OLED-Display anzeigen.
*   **FR-2.2:** Das System MUSS die aktuelle Luftfeuchtigkeit auf dem SSD1306 OLED-Display anzeigen.
*   **FR-2.3:** Das System MUSS den aktuellen Luftdruck auf dem SSD1306 OLED-Display anzeigen.
*   **FR-2.4:** Die Anzeige auf dem OLED-Display MUSS mindestens alle 1 Sekunde aktualisiert werden.
*   **FR-2.5:** Die Anzeigewerte MÜSSEN klar lesbar sein und die entsprechenden Einheiten (z.B. °C, %RH, hPa) enthalten.

### 3.3 Konfiguration
*   **FR-3.1:** Konfigurationsparameter wie Display-Dimensionen, I2C-Adressen der Sensoren und Displays sowie Seedruckhöhe MÜSSEN in einer dedizierten Header-Datei (`config.h`) zentral definiert sein.

### 3.4 Fehlerbehandlung
*   **FR-4.1:** Das System MUSS eine Fehlermeldung auf der seriellen Konsole ausgeben, wenn das OLED-Display nicht initialisiert werden kann.
*   **FR-4.2:** Das System MUSS eine Fehlermeldung auf der seriellen Konsole ausgeben, wenn der BME280-Sensor nicht initialisiert werden kann.
*   **FR-4.3:** Bei einem kritischen Initialisierungsfehler (Display oder Sensor) MUSS das System in einem Fehlermodus verbleiben oder den Betrieb einstellen.

## 4. Nicht-funktionale Anforderungen

### 4.1 Leistung
*   **NFR-1.1:** Die Sensordatenerfassung und die Displayaktualisierung MÜSSEN parallel und ohne spürbare Verzögerung erfolgen.
*   **NFR-1.2:** Die Verwendung von FreeRTOS MUSS eine effiziente Ressourcenverwaltung gewährleisten.

### 4.2 Zuverlässigkeit
*   **NFR-2.1:** Das System MUSS unterbrechungsfrei über längere Zeiträume (Wochen/Monate) funktionieren.
*   **NFR-2.2:** I2C-Kommunikationsfehler SOLLTEN robust behandelt werden, um Systemabstürze zu vermeiden.

### 4.3 Wartbarkeit
*   **NFR-3.1:** Der Code MUSS modular und leicht verständlich sein, unterteilt in logische Header-Dateien.
*   **NFR-3.2:** Die Konfiguration des Systems MUSS einfach durch Anpassung von `config.h` möglich sein.

### 4.4 Sicherheit (Physisch)
*   **NFR-4.1:** Das System SOLLTE in einem Gehäuse untergebracht werden, um die Elektronik vor Umwelteinflüssen zu schützen (extern, nicht Teil dieser Spezifikation).

### 4.5 Benutzerfreundlichkeit (Anzeige)
*   **NFR-5.1:** Die angezeigten Informationen MÜSSEN auf einen Blick erfassbar sein.

## 5. Technische Architektur (Kurz)

### 5.1 Hardware-Komponenten
*   **Mikrocontroller:** ESP32 (ESP32 Dev Module)
*   **Sensor:** BME280 (Temperatur, Luftfeuchtigkeit, Druck)
*   **Display:** SSD1306 OLED (I2C, 128x64 Pixel)

### 5.2 Software-Komponenten
*   **Echtzeitbetriebssystem:** FreeRTOS
*   **Programmiersprache:** C++ (Arduino-Framework)
*   **Bibliotheken:**
    *   `Wire.h` (I2C-Kommunikation)
    *   `Adafruit_GFX.h` (Grafikbibliothek für Displays)
    *   `Adafruit_SSD1306.h` (Treiber für SSD1306 OLED)
    *   `Adafruit_BME280.h` (Treiber für BME280-Sensor)

## 6. Schnittstellen

### 6.1 Benutzeroberfläche (OLED)
*   Anzeige von Temperatur, Luftfeuchtigkeit und Luftdruck.

### 6.2 Hardware-Schnittstellen
*   **I2C-Bus:** Verwendung von GPIO 21 (SDA) und GPIO 22 (SCL) des ESP32.
*   **Spannungsversorgung:** 3.3V für ESP32, BME280 und SSD1306.

### 6.3 Serielle Schnittstelle
*   Verwendung der seriellen Schnittstelle für Debugging-Ausgaben bei 115200 Baud.

## 7. Offene Punkte / Zukünftige Erweiterungen

*   **WLAN-Anbindung:** Integration einer Funktion zur Übertragung der Wetterdaten an einen Server oder Cloud-Dienst.
*   **Datenlogging:** Speicherung der historischen Wetterdaten auf einer SD-Karte oder im internen Flash-Speicher des ESP32.
*   **Webserver:** Implementierung eines einfachen Webservers auf dem ESP32 zur Anzeige der Daten im lokalen Netzwerk.
*   **Kalibrierung:** Möglichkeit zur Kalibrierung der Sensordaten.
*   **Uhrzeit:** Integration einer Echtzeituhr (RTC) zur Zeitstempelung der Daten.
