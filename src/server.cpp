#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include <SPIFFS.h>
#include "settings.h"

int distance;

void initWifi()
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
void webServer()
{
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.on("/data/pir", HTTP_GET, [&](AsyncWebServerRequest *request)
            { 
              String ptr = "{";
              ptr += "\"value\": ";
              if(state == LOW){
                ptr += "\"1\"";
              } else {
                ptr += "\"0\"";
              }
              ptr += "}";

              request->send(200, "application/json", ptr); });

  server.on("/data/sound", HTTP_GET, [&](AsyncWebServerRequest *request)
            { 
              String ptr = "{";
              ptr += "\"value\": ";
              ptr += distance;
              ptr += "}"; 
              
              request->send(200, "application/json", ptr); });

  server.begin();
  Serial.println("HTTP server started");
  readFiles();
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
