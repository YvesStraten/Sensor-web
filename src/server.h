#pragma once
#include "pins.h"

namespace ESP32Server {
  void initWifi();
  void readFiles();
  void webServer(String Json1, String Json2);
  String JsonFactory(int component, PinStates &state);
}