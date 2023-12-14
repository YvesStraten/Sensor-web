#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <Arduino.h>
#include <SPIFFS.h>
#include "settings.h"
#include "server.h"
#include "pins.h"

void ESP32Server::initWifi()
{
  Serial.begin(9600);
  delay(5000);
  Serial.println("Loading AP and server");
  WiFi.softAP(ssid);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  Serial.println(WiFi.broadcastIP().toString().c_str());
}

/* Server functions:
- Serve static files
- Allow for data requests */
void ESP32Server::webServer(String Json1, String Json2)
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
void ESP32Server::readFiles()
{
  if (!SPIFFS.begin(true))
  {
    Serial.println("Error mounting SPIFFS!");
    return;
  }
}

String ESP32Server::JsonFactory(int component, PinStates &state)
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
    ptr += state.distance;
  }
    ptr += "}";
  return ptr;
}