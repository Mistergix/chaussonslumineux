
const char DOUT_TRIGGER = 7;
const char DIN_ECHO = 6;
float distance;

void setup(){
  Serial.begin(9600);
    pinMode(DOUT_TRIGGER, OUTPUT);
    pinMode(DIN_ECHO, INPUT);
    pinMode(3,OUTPUT);
  }
void loop()
  {
    digitalWrite(DOUT_TRIGGER, LOW);
    delayMicroseconds(2);
    digitalWrite(DOUT_TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(DOUT_TRIGGER, LOW);
    distance= pulseIn(DIN_ECHO, HIGH) / 58.0;
    Serial.println(distance);
    delay(500);
    if (distance<20){
      digitalWrite(3, HIGH);
    }
    else{
      digitalWrite(3,LOW);
      }
    }
