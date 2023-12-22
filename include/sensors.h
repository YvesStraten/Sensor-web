#ifndef SENSORS_H_
#define SENSORS_H_

#include <Arduino.h>

struct PinStates 
{
    int distance;

    // PIR states
    int pirVal = -1;
    int pirState = LOW;
};

void getDistance(PinStates &states);
void getMotion(PinStates &states);
char* jsonFactory(PinStates &state);

#endif