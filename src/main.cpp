#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include "settings.h"
#include "sensors.h"

AsyncWebServer server(80);

PinStates states;
char* Json1;
char* Json2;

/* Server functions:
- Serve static files
- Allow for data requests */
void webServer()
{
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.on("/data/pir", HTTP_GET, [&](AsyncWebServerRequest *request)
            { request->send(200, "application/json", Json1); });

  server.on("/data/sound", HTTP_GET, [&](AsyncWebServerRequest *request)
            {  request->send(200, "application/json", Json2); });

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
  Json1 = jsonFactory(0, states);
  Json2 = jsonFactory(1, states);
}