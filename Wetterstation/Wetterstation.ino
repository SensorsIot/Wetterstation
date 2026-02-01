#include "tasks.h"

void setup() {
  Serial.begin(115200);
  
  // 1. Mutex erstellen (Bevor wir I2C nutzen!)
  i2cMutex = xSemaphoreCreateMutex();

  // 2. Hardware Initialisierung (Einmalig, Thread-Safe machen wir hier manuell)
  Wire.begin(21, 22);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Display Fehler"));
    for(;;);
  }
  display.clearDisplay();
  display.display();

  if (!bme.begin(BME_ADDRESS)) {
    Serial.println("Sensor Fehler");
    while (1);
  }

  // 3. Tasks erstellen
  // Name, Stack-Größe, Parameter, Priorität, Handle, Core-ID
  xTaskCreatePinnedToCore(taskMeasure, "MeasureTask", 4096, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(taskDisplay, "DisplayTask", 4096, NULL, 1, NULL, 1);
}

void loop() {
  // Der Loop ist jetzt LEER und FREI!
  // Hier könntest du später z.B. Wifi Checken oder LEDs blinken lassen
  // ohne das Display oder Sensor zu stören.
  vTaskDelay(pdMS_TO_TICKS(1000)); // Kleines Delay damit der Watchdog nicht bellt
}