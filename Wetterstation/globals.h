#ifndef GLOBALS_H
#define GLOBALS_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BME280.h>
#include "config.h"

// --- Globale Objekte ---
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_BME280 bme;

// --- RTOS Globale Variablen ---
SemaphoreHandle_t i2cMutex; // Der "Schlüssel" für den I2C Bus

// Struktur für die Wetterdaten (zum Austausch zwischen Tasks)
struct WeatherData {
  float temp;
  float hum;
  float pres;
};
WeatherData currentData;

#endif