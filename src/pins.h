#pragma once
#include <Arduino.h>

struct PinStates 
{
    // ECHO pulse and duration
    int pulse;
    int distance;

    // PIR states
    int pirVal = -1;
    int pirState = LOW;
};

extern PinStates states;

namespace Pins
{
    void getDistance(PinStates &states);

    void getMotion(PinStates &states);

    void pinSetup();
}