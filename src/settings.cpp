#include "settings.h"

AsyncWebServer server(80);
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Defines pins
int trigPin = 26;
int echoPin = 36;
int pirPin = 39;
int ledPin = 12;

const char *ssid = "ESP Web server";
// const char *ssid = "test123";
// const char *pass = "12345678";