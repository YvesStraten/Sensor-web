#include "settings.h"
#include "sensor.h"
#include <ESPAsyncWebServer.h>

// Defines pins
int trigPin = 26;
int echoPin = 36;
int pirPin = 39;
int ledPin = 12;

const char *ssid = "ESP Web server";
// const char *ssid = "test123";
// const char *pass = "12345678";

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void pinSetup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
};

void initWifi()
{
  Serial.begin(9600);
  delay(5000);
  Serial.println("Loading AP and server");
  // WiFi.begin(ssid, pass);
  WiFi.softAP(ssid);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  Serial.println(WiFi.broadcastIP().toString().c_str());
}