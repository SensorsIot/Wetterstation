#pragma once

#include <Adafruit_BME280.h>

struct SensorData {
    float temperature;
    float humidity;
    float pressure;
    bool  valid;
};

bool sensor_init();
SensorData sensor_read();
SensorData sensor_get_last();
