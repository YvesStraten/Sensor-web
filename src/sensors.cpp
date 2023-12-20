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

char *jsonFactory(int component, PinStates &state)
{
  // Empty array (string)
  char *json;
  /* Allocates 32 bytes to the array while casting it back to a char**/
  json = (char *)malloc(32);

  if (json == NULL)
  {
    Serial.println("Malloc failed");
    return NULL;
  }
  
  // We know its the PIR then
  if (component == 0)
  {
    // Motion
    if (state.pirState == LOW)
    {
      snprintf(json, 32, "{ \"value\": %d }", 1);
    }
    else
    // No motion
    {
      snprintf(json, 32, "{ \"value\": %d }", 0);
    }
  }
  else
  {
    // Distance of sensor
    snprintf(json, 32, "{ \"value\": %d }", state.distance);
  }
  return json;
}
