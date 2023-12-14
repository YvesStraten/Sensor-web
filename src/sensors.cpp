#include "sensors.h"
#include "settings.h"

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

  if (states.distance < 200)
  {
    digitalWrite(ledPin, HIGH);
    delay(1000);
  }

  digitalWrite(ledPin, LOW);
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
    }
  }
  else
  {
    if (states.pirState == HIGH)
    {
      states.pirState = LOW;
    }
  }
}