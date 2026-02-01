#pragma once

#include "sensor.h"

bool display_init();
void display_show_data(const SensorData &data);
void display_show_error(const char *message);
