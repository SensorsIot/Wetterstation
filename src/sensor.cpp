#include "sensor.h"
#include "config.h"
#include <Wire.h>

static Adafruit_BME280 bme;
static SensorData lastData = {0, 0, 0, false};
static SemaphoreHandle_t dataMutex = xSemaphoreCreateMutex();

bool sensor_init() {
    Wire.begin(I2C_SDA, I2C_SCL);
    if (!bme.begin(BME280_ADDR, &Wire)) {
        Serial.println("[FEHLER] BME280 nicht gefunden! Adresse: 0x76");
        return false;
    }
    Serial.println("[OK] BME280 initialisiert");
    return true;
}

SensorData sensor_read() {
    SensorData data;
    data.temperature = bme.readTemperature();
    data.humidity    = bme.readHumidity();
    data.pressure    = bme.readPressure() / 100.0F;
    data.valid       = !isnan(data.temperature) && !isnan(data.humidity) && !isnan(data.pressure);

    if (data.valid) {
        xSemaphoreTake(dataMutex, portMAX_DELAY);
        lastData = data;
        xSemaphoreGive(dataMutex);
    } else {
        Serial.println("[FEHLER] Ungueltige Sensordaten!");
    }

    return data;
}

SensorData sensor_get_last() {
    SensorData data;
    xSemaphoreTake(dataMutex, portMAX_DELAY);
    data = lastData;
    xSemaphoreGive(dataMutex);
    return data;
}
