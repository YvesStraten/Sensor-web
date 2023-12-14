#ifndef SETTINGS_H_
#define SETTINGS_H_
#include <ESPAsyncWebServer.h>

// Defines pins
extern int trigPin;
extern int echoPin;
extern int pirPin;
extern int ledPin;

extern const char *ssid;
extern const char *pass;

extern void pinSetup();
extern void initWifi();
#endif