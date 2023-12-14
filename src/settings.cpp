#include "settings.h"
#include <ESPAsyncWebServer.h>

// Defines pins
int trigPin = 26;
int echoPin = 36;
int pirPin = 39;
int ledPin = 12;

const char *ssid = "ESP Web server";
// const char *ssid = "test123";
// const char *pass = "12345678";

void pinSetup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
};