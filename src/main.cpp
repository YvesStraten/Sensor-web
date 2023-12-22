#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include "settings.h"
#include "sensors.h"

AsyncWebServer server(80);

PinStates states;
char* json;

/* Server functions:
- Serve static files
- Allow for data requests */
void webServer()
{
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.on("/api/data", HTTP_GET, [&](AsyncWebServerRequest *request)
            { request->send(200, "application/json", json); });

  server.begin();
  Serial.println("HTTP server started");
}

// Initializes SPIFFS storage
void readFiles()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("Error mounting SPIFFS!");
    return;
  }
}

void setup()
{
  initWifi();
  readFiles();

  pinSetup();
  webServer();
}

void loop()
{
  getDistance(states);
  getMotion(states);
  json = jsonFactory(0, states);
}