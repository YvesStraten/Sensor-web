#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


const char *ssid = "ESP Web server";
// const char *ssid = "test123";
// const char *pass = "12345678";

// Defines server and its static IP

// ECHO pulse and duration
int pulse;
int distance;

// PIR states
int pirVal = 0;
int state = LOW;