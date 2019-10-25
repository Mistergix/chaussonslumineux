#include <CapacitiveSensor.h>
CapacitiveSensor capSensor=CapacitiveSensor(4,2);
const int button1Pin = 2;
int cst=50;
const int ledPin=12;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  long sensorValue=capSensor.capacitiveSensor(30);

  if (sensorValue > cst){
      digitalWrite(ledPin,HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }
  Serial.println(sensorValue);
  delay(10);
}
