#include "display.h"
#include "config.h"
#include <Adafruit_SSD1306.h>
#include <Wire.h>

static Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool display_init() {
    if (!oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("[FEHLER] SSD1306 nicht gefunden!");
        return false;
    }
    oled.clearDisplay();
    oled.setTextColor(SSD1306_WHITE);
    oled.setTextSize(1);
    oled.setCursor(0, 20);
    oled.println("Wetterstation");
    oled.println("startet...");
    oled.display();
    Serial.println("[OK] OLED Display initialisiert");
    return true;
}

void display_show_data(const SensorData &data) {
    oled.clearDisplay();

    // Titel
    oled.setTextSize(1);
    oled.setCursor(0, 0);
    oled.println("== Wetterstation ==");

    // Temperatur
    oled.setCursor(0, 16);
    oled.print("Temp:  ");
    oled.print(data.temperature, 1);
    oled.println(" C");

    // Luftfeuchtigkeit
    oled.setCursor(0, 30);
    oled.print("Feuchte: ");
    oled.print(data.humidity, 1);
    oled.println(" %");

    // Luftdruck
    oled.setCursor(0, 44);
    oled.print("Druck: ");
    oled.print(data.pressure, 1);
    oled.println(" hPa");

    oled.display();
}

void display_show_error(const char *message) {
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setCursor(0, 0);
    oled.println("!! FEHLER !!");
    oled.setCursor(0, 20);
    oled.println(message);
    oled.display();
}
