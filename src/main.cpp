#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include "settings.h"
#include "server.h"

// Defines pins
int trigPin = 26;
int echoPin = 36;
int pirPin = 39;
int ledPin = 12;

// Sets pins to the right modes
void pinSetup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
};

void setup()
{
  initWifi();
  pinSetup();
  webServer();
}

// Gets distance from ultrasonic sensor
void getDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pulse = pulseIn(echoPin, HIGH);
  distance = pulse * 0.034 / 2;

  // Serial.print("Duration: ");
  // Serial.println(distance);
  delay(1000);

  if (distance < 200)
  {
    digitalWrite(ledPin, HIGH);
    delay(1000);
  }

  digitalWrite(ledPin, LOW);
}

// Get the motion state of the PIR
void getMotion()
{
  pirVal = digitalRead(pirPin);
  if (pirVal == HIGH)
  {
    if (state == LOW)
    {
      state = HIGH;
    }
  }
  else
  {
    if (state == HIGH)
    {
      state = LOW;
    }
  }
}

void loop()
{
  getDistance();
  getMotion();
}