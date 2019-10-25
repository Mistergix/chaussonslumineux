const int ledPin = 9;
const int photoSensorPin = A0;
int sensorValue = 0;
int threshold = 700;

const char DOUT_TRIGGER = 7;
const char DIN_ECHO = 6;
float distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(DOUT_TRIGGER, OUTPUT);
  pinMode(DIN_ECHO, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(photoSensorPin);
  delay(5);
  Serial.print("Sensor Value : ");
  Serial.println(sensorValue);

  digitalWrite(DOUT_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(DOUT_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(DOUT_TRIGGER, LOW);
  distance= pulseIn(DIN_ECHO, HIGH) / 58.0;

  Serial.print("Distance : ");
  Serial.println(distance);

  if(sensorValue < threshold && distance < 20) {
      digitalWrite(ledPin, HIGH);
  }
  else {
      digitalWrite(ledPin, LOW);
    }
  }
