#include "ota.h"
#include <ArduinoOTA.h>

void ota_init() {
    ArduinoOTA.setHostname("wetterstation");

    ArduinoOTA.onStart([]() {
        Serial.println("[OTA] Update startet...");
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\n[OTA] Update fertig!");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("[OTA] Fortschritt: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("[OTA FEHLER] %u: ", error);
        if (error == OTA_AUTH_ERROR)         Serial.println("Auth fehlgeschlagen");
        else if (error == OTA_BEGIN_ERROR)   Serial.println("Begin fehlgeschlagen");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Verbindung fehlgeschlagen");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Empfang fehlgeschlagen");
        else if (error == OTA_END_ERROR)     Serial.println("Ende fehlgeschlagen");
    });

    ArduinoOTA.begin();
    Serial.println("[OK] OTA bereit");
}

void ota_handle() {
    ArduinoOTA.handle();
}
