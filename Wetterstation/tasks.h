#ifndef TASKS_H
#define TASKS_H

#include "globals.h"

// --- Task Definitionen ---

// Task 1: Misst alle 2 Sekunden die Werte
void taskMeasure(void *pvParameters) {
  for (;;) { // Endlosschleife (ersetzt loop)
    
    // Wir fordern den Zugriff auf den I2C Bus an
    if (xSemaphoreTake(i2cMutex, portMAX_DELAY) == pdTRUE) {
      // Zugriff erhalten! Messen:
      currentData.temp = bme.readTemperature();
      currentData.hum = bme.readHumidity();
      currentData.pres = bme.readPressure() / 100.0F;
      
      // Zugriff wieder freigeben
      xSemaphoreGive(i2cMutex);
    }

    // Seriell zur Kontrolle (optional)
    Serial.print("Messung: "); Serial.println(currentData.temp);

    // 2 Sekunden warten (blockiert andere Tasks NICHT!)
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

// Task 2: Aktualisiert das Display (unabhängig vom Messen)
void taskDisplay(void *pvParameters) {
  for (;;) {
    
    // Wir fordern den Zugriff an (weil Display auch I2C nutzt)
    if (xSemaphoreTake(i2cMutex, portMAX_DELAY) == pdTRUE) {
      
      display.clearDisplay();
      display.setTextSize(2);      
      display.setTextColor(SSD1306_WHITE);

      // Zeile 1: Temperatur
      display.setCursor(0, 0);     
      display.print(currentData.temp, 1);      
      display.print(" C");        

      // Zeile 2: Luftfeuchtigkeit
      display.setCursor(0, 22);    
      display.print(currentData.hum, 0);       
      display.print(" %RH");

      // Zeile 3: Luftdruck
      display.setCursor(0, 44);    
      display.print(currentData.pres, 0);      
      display.print(" hPa");

      display.display();
      
      // Zugriff wieder freigeben
      xSemaphoreGive(i2cMutex);
    }

    // Wir aktualisieren das Display alle 1 Sekunde (oder wie gewünscht)
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

#endif