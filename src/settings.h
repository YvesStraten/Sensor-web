#ifndef SETTINGS_H
#define SETTINGS_H
#include <ESPAsyncWebServer.h>

extern AsyncWebServer server;
extern IPAddress local_ip;
extern IPAddress gateway;
extern IPAddress subnet;

// Defines pins
extern int trigPin;
extern int echoPin;
extern int pirPin;
extern int ledPin;

extern const char *ssid;
// const char *pass;
#endif