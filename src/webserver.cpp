#include "webserver.h"
#include "sensor.h"
#include "config.h"
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

static AsyncWebServer server(80);
static DNSServer dnsServer;

static const char HTML_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Wetterstation</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
            color: #333;
        }
        .container {
            background: rgba(255,255,255,0.95);
            border-radius: 20px;
            padding: 30px;
            width: 340px;
            box-shadow: 0 20px 60px rgba(0,0,0,0.3);
        }
        h1 {
            text-align: center;
            font-size: 1.4em;
            margin-bottom: 20px;
            color: #4a4a8a;
        }
        .card {
            background: #f8f9ff;
            border-radius: 12px;
            padding: 16px 20px;
            margin-bottom: 12px;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        .card:last-child { margin-bottom: 0; }
        .label { font-size: 0.95em; color: #666; }
        .value { font-size: 1.5em; font-weight: 700; color: #4a4a8a; }
        .unit { font-size: 0.7em; font-weight: 400; color: #999; }
        .status {
            text-align: center;
            margin-top: 16px;
            font-size: 0.8em;
            color: #999;
        }
        .error { color: #e74c3c; font-weight: bold; }
    </style>
</head>
<body>
    <div class="container">
        <h1>Wetterstation</h1>
        <div class="card">
            <span class="label">Temperatur</span>
            <span class="value" id="temp">--<span class="unit"> &deg;C</span></span>
        </div>
        <div class="card">
            <span class="label">Luftfeuchtigkeit</span>
            <span class="value" id="hum">--<span class="unit"> %</span></span>
        </div>
        <div class="card">
            <span class="label">Luftdruck</span>
            <span class="value" id="pres">--<span class="unit"> hPa</span></span>
        </div>
        <div class="status" id="status">Verbinde...</div>
    </div>
    <script>
        function update() {
            fetch('/api/data')
                .then(r => r.json())
                .then(d => {
                    if (d.valid) {
                        document.getElementById('temp').innerHTML = d.temperature.toFixed(1) + '<span class="unit"> &deg;C</span>';
                        document.getElementById('hum').innerHTML = d.humidity.toFixed(1) + '<span class="unit"> %</span>';
                        document.getElementById('pres').innerHTML = d.pressure.toFixed(1) + '<span class="unit"> hPa</span>';
                        document.getElementById('status').textContent = 'Aktualisiert: ' + new Date().toLocaleTimeString();
                        document.getElementById('status').className = 'status';
                    } else {
                        document.getElementById('status').textContent = 'Sensorfehler!';
                        document.getElementById('status').className = 'status error';
                    }
                })
                .catch(() => {
                    document.getElementById('status').textContent = 'Verbindungsfehler!';
                    document.getElementById('status').className = 'status error';
                });
        }
        update();
        setInterval(update, 2000);
    </script>
</body>
</html>
)rawliteral";

void webserver_init() {
    // DNS: Alle Anfragen auf unsere IP umleiten (Captive Portal)
    dnsServer.start(53, "*", AP_IP);

    // Hauptseite
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", HTML_PAGE);
    });

    // JSON API fuer Sensordaten
    server.on("/api/data", HTTP_GET, [](AsyncWebServerRequest *request) {
        SensorData data = sensor_get_last();
        String json = "{";
        json += "\"temperature\":" + String(data.temperature, 1) + ",";
        json += "\"humidity\":" + String(data.humidity, 1) + ",";
        json += "\"pressure\":" + String(data.pressure, 1) + ",";
        json += "\"valid\":" + String(data.valid ? "true" : "false");
        json += "}";
        request->send(200, "application/json", json);
    });

    // Captive Portal: Alle unbekannten Anfragen auf Hauptseite umleiten
    server.onNotFound([](AsyncWebServerRequest *request) {
        request->redirect("http://192.168.4.1/");
    });

    server.begin();
    Serial.println("[OK] Webserver gestartet auf 192.168.4.1");

    // DNS-Task fuer Captive Portal
    xTaskCreatePinnedToCore(
        [](void *) {
            for (;;) {
                dnsServer.processNextRequest();
                vTaskDelay(pdMS_TO_TICKS(10));
            }
        },
        "dns_task", 2048, NULL, 1, NULL, 0
    );
}
