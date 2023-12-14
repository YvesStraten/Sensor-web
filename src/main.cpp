#include <Arduino.h>
#include "server.h"
#include "pins.h"

using namespace ESP32Server;
using namespace Pins;

PinStates states;
String Json1;
String Json2;

void setup()
{
  initWifi();
  readFiles();
  webServer(Json1, Json2);

  pinSetup();
}

void loop()
{
  getDistance(states);
  getMotion(states);
  Json1 = JsonFactory(0, states);
  Json2 = JsonFactory(1, states);
}