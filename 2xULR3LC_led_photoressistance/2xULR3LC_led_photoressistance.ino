#include <Wire.h>
#include <VL53L0X.h>
const int ledPin = 2;
const int photoSensorPin = A0;
int photosensorValue = 0;
int photothreshold = 700;
int distancethreshold = 200;

//#define XSHUT_pin6 not required for address change

#define XSHUT_pin2 8
#define XSHUT_pin1 7

//ADDRESS_DEFAULT 0b0101001 or 41
//#define Sensor1_newAddress 41 not required address change
#define Sensor2_newAddress 42


VL53L0X Sensor1;
VL53L0X Sensor2;


void setup()
{ /*WARNING*/
  //Shutdown pins of VL53L0X ACTIVE-LOW-ONLY NO TOLERANT TO 5V will fry them
  pinMode(XSHUT_pin1, OUTPUT);
  pinMode(XSHUT_pin2, OUTPUT);
  pinMode(ledPin, OUTPUT);

  
  Serial.begin(9600);
  
  Wire.begin();
  //Change address of sensor and power up next one

  Sensor2.setAddress(Sensor2_newAddress);
  pinMode(XSHUT_pin1, INPUT);
  delay(10);
  
  Sensor1.init();
  Sensor2.init();

  
  Sensor1.setTimeout(500);
  Sensor2.setTimeout(500);
 

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  Sensor1.startContinuous();
  Sensor2.startContinuous();

}

void loop()
{
  int distance=Sensor1.readRangeContinuousMillimeters();

  Serial.println("Capteur1 " + (String)Sensor1.readRangeContinuousMillimeters());
  Serial.print(Sensor2.readRangeContinuousMillimeters());
  Serial.print(',');
  photosensorValue = analogRead(photoSensorPin);
  if(photosensorValue < photothreshold && distance < distancethreshold ) {
      digitalWrite(ledPin, HIGH);
  }
  else {
      digitalWrite(ledPin, LOW);
}
}
