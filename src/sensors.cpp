#include "sensors.h"
#include "settings.h"
#include <iostream>

// Gets distance from ultrasonic sensor
void getDistance(PinStates &states)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int pulse = pulseIn(echoPin, HIGH);
  states.distance = pulse * 0.034 / 2;

  // Serial.print("Duration: ");
  // Serial.println(distance);
  delay(1000);
}

// Get the motion state of the PIR
void getMotion(PinStates &states)
{
  states.pirVal = digitalRead(pirPin);
  if (states.pirVal == HIGH)
  {
    if (states.pirState == LOW)
    {
      states.pirState = HIGH;
      delay(1000);
    }
  }
  else
  {
    if (states.pirState == HIGH)
    {
      states.pirState = LOW;
      delay(1000);
    }
  }
}

char *jsonFactory(PinStates &state)
{
  // Empty array (string)
  char *json;
  int size = 42 + sizeof(state.pirState) + sizeof(state.distance);

  // We know its the PIR then
  {
    json = (char *)malloc(size);
    // Motion
    if (state.pirState == LOW)
    {
      snprintf(json, size, "{ \"sensors\": { \"pir\": %d, \"sound\": %d } }", 1, state.distance);
    }
    else
    // No motion
    {
      snprintf(json, size, "{ \"sensors\": { \"pir\": %d, \"sound\": %d } }", 0, state.distance);
    }

    if (json == NULL)
    {
      Serial.println("Malloc failed");
    }

    // Serial.println(json);
    return json;
  }
