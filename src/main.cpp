#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "sensor.h"
#include "display.h"
#include "webserver.h"
#include "ota.h"

static bool sensorOk = false;
static bool displayOk = false;

// RTOS Task: Sensor alle 2 Sekunden auslesen + seriell ausgeben
void sensorTask(void *param) {
    for (;;) {
        SensorData data = sensor_read();

        if (data.valid) {
            Serial.printf("[Sensor] Temp: %.1f C | Feuchte: %.1f %% | Druck: %.1f hPa\n",
                          data.temperature, data.humidity, data.pressure);
        }

        vTaskDelay(pdMS_TO_TICKS(SENSOR_INTERVAL_MS));
    }
}

// RTOS Task: Display alle 2 Sekunden aktualisieren
void displayTask(void *param) {
    for (;;) {
        SensorData data = sensor_get_last();

        if (data.valid) {
            display_show_data(data);
        } else {
            display_show_error("Keine Sensordaten");
        }

        vTaskDelay(pdMS_TO_TICKS(SENSOR_INTERVAL_MS));
    }
}

// RTOS Task: OTA handle
void otaTask(void *param) {
    for (;;) {
        ota_handle();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("\n=== Wetterstation ===\n");

    // Display initialisieren
    displayOk = display_init();
    if (!displayOk) {
        Serial.println("[FEHLER] Display konnte nicht initialisiert werden!");
    }

    // Sensor initialisieren
    sensorOk = sensor_init();
    if (!sensorOk) {
        Serial.println("[FEHLER] Sensor konnte nicht initialisiert werden!");
        if (displayOk) {
            display_show_error("BME280 nicht\ngefunden!");
        }
    }

    // Wi-Fi Access Point starten
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(AP_IP, AP_GATEWAY, AP_SUBNET);
    WiFi.softAP(AP_SSID);
    Serial.print("[OK] AP gestartet: ");
    Serial.println(AP_SSID);
    Serial.print("[OK] IP: ");
    Serial.println(WiFi.softAPIP());

    // OTA initialisieren
    ota_init();

    // Webserver + Captive Portal starten
    webserver_init();

    // RTOS Tasks starten
    if (sensorOk) {
        xTaskCreatePinnedToCore(sensorTask,  "sensor_task",  SENSOR_TASK_STACK,  NULL, SENSOR_TASK_PRIO,  NULL, 1);
    }
    if (displayOk) {
        xTaskCreatePinnedToCore(displayTask, "display_task", DISPLAY_TASK_STACK, NULL, DISPLAY_TASK_PRIO, NULL, 1);
    }
    xTaskCreatePinnedToCore(otaTask, "ota_task", 4096, NULL, 1, NULL, 0);

    Serial.println("\n[OK] Wetterstation bereit!\n");
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}
