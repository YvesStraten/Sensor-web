#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

// const char* ssid = "ESP Web server";
const char *ssid = "test123";
const char *pass = "12345678";

AsyncWebServer server(80);
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Initialize json
StaticJsonDocument<32> pir;
StaticJsonDocument<32> soundData;
String pirString;
String soundDataString;

int trigPin = 26;
int echoPin = 36;
int pirPin = 39;
int ledPin = 12;

// ECHO pulse and duration
int pulse;
int distance;

// PIR state
int pirVal = 0;
int state = LOW;

void initWifi()
{
  WiFi.begin(ssid, pass);
  // WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  Serial.println(WiFi.localIP().toString().c_str());
}

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
  Serial.begin(9600);
  delay(5000);
  Serial.println("Loading AP and server");
  initWifi();

  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.on("/data/pir", HTTP_GET, [&](AsyncWebServerRequest *request)
            { request->send(200, "application/json", pirString); });

  server.on("/data/sound", HTTP_GET, [&](AsyncWebServerRequest *request)
            {
              request->send(200, "application/json", soundDataString);
            });

  server.begin();
  Serial.println("HTTP server started");
  readFiles();
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pulse = pulseIn(echoPin, HIGH);
  distance = pulse * 0.034 / 2;
  soundData["value"] = distance;
  // soundDataString = soundData.as<const char*>();

  // Serial.print("Duration: ");
  // Serial.println(distance);
  delay(1000);

  if (distance < 200)
  {
    digitalWrite(ledPin, HIGH);
    delay(1000);
  }

  digitalWrite(ledPin, LOW);

  pirVal = digitalRead(pirPin);
  if (pirVal == HIGH)
  {
    if (state == LOW)
    {
      Serial.println("MOTION");
      pir["value"] = 1;
      state = HIGH;
    }
  }
  else
  {
    if (state == HIGH)
    {
      Serial.println("NO MOTION");
      pir["value"] = 0;
      state = LOW;
    }
  }

  // pirString = pir.as<const char*>();
}