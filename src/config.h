#pragma once

// --- Wi-Fi Access Point ---
#define AP_SSID       "Wetterstation"
#define AP_IP         IPAddress(192, 168, 4, 1)
#define AP_GATEWAY    IPAddress(192, 168, 4, 1)
#define AP_SUBNET     IPAddress(255, 255, 255, 0)

// --- I2C Pins (ESP32 Default) ---
#define I2C_SDA       21
#define I2C_SCL       22

// --- BME280 ---
#define BME280_ADDR   0x76

// --- OLED Display (SSD1306 128x64) ---
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

// --- Timing ---
#define SENSOR_INTERVAL_MS  2000

// --- RTOS ---
#define SENSOR_TASK_STACK   4096
#define DISPLAY_TASK_STACK  4096
#define SENSOR_TASK_PRIO    2
#define DISPLAY_TASK_PRIO   1
