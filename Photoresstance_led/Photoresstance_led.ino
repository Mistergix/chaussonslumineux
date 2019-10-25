const int ledPin = 9;
const int photoSensorPin = A0;
int sensorValue = 0;
int threshold = 700 ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(photoSensorPin);
  delay(5);
  Serial.print("Value :");
  Serial.println(sensorValue);

  if(sensorValue < threshold) {
      digitalWrite(ledPin, HIGH);
  }
  else {
      digitalWrite(ledPin, LOW);
    }
  }
