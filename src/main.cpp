#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include "settings.h"
#include "sensors.h"

AsyncWebServer server(80);

PinStates states;
String Json1;
String Json2;

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

String JsonFactory(int component, PinStates &state)
{
  String ptr;
  ptr = "{";
  ptr += "\"value\": ";
  // We know its the PIR then
  if (component == 0)
  {
    if (state.pirState == LOW)
    {
      ptr += "\"1\"";
    }
    else
    {
      ptr += "\"0\"";
    }
  } else {
    ptr += "\"";
    ptr += state.distance;
    ptr += "\"";
  }
    ptr += "}";
  return ptr;
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
  Json1 = JsonFactory(0, states);
  Json2 = JsonFactory(1, states);
}