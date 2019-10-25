const int ledPin = 9;
const int photoSensorPin = A0;
int photosensorValue = 0;
int photothreshold = 700;

const char DOUT_TRIGGER = 7;
const char DIN_ECHO = 6;
float distance;
#include <CapacitiveSensor.h>
CapacitiveSensor capSensor=CapacitiveSensor(4,2);
int capacitivethreshold=50;

int distancethreshold = 20;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(DOUT_TRIGGER, OUTPUT);
  pinMode(DIN_ECHO, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  photosensorValue = analogRead(photoSensorPin);
  long capacitivesensorValue=capSensor.capacitiveSensor(30);
  delay(5);
  Serial.print("capacitive Sensor Value : ");
  Serial.println(capacitivesensorValue);

  Serial.print("photo Sensor Value : ");
  Serial.println(photosensorValue);

  digitalWrite(DOUT_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(DOUT_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(DOUT_TRIGGER, LOW);
  distance= pulseIn(DIN_ECHO, HIGH) / 58.0;

  Serial.print("Distance : ");
  Serial.println(distance);

  if(photosensorValue < photothreshold && distance < distancethreshold && capacitivesensorValue > capacitivethreshold) {
      digitalWrite(ledPin, HIGH);
  }
  else {
      digitalWrite(ledPin, LOW);
    }
  }
