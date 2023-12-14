#include "pins.h"
#include "settings.h"

// Sets pins to the right modes
void Pins::pinSetup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
};

// Gets distance from ultrasonic sensor
void Pins::getDistance(PinStates &states)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  states.pulse = pulseIn(echoPin, HIGH);
  states.distance = states.pulse * 0.034 / 2;

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
void Pins::getMotion(PinStates &states)
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
