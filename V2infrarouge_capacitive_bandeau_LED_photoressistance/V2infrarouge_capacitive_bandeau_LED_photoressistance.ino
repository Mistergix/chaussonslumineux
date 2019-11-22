#include <Wire.h>
#include <VL53L0X.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define XSHUT_pin2 8
#define XSHUT_pin1 7

#define LEDSTRIP_PIN 6
#define NB_PIXELS 11

const int ledPin = 5;
const int ledPin2 = 3;

const int photoSensorPin = A0;
int photosensorValue = 0;
int photothreshold = 700;
int distancethreshold = 200;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NB_PIXELS, LEDSTRIP_PIN, NEO_GRB + NEO_KHZ800);

//ADDRESS_DEFAULT 0b0101001 or 41
//#define Sensor1_newAddress 41 not required address change
#define Sensor2_newAddress 42

VL53L0X Sensor1;
VL53L0X Sensor2;

#include <CapacitiveSensor.h>
CapacitiveSensor capSensor=CapacitiveSensor(4,2);
int capacitivethreshold=50;

void setup()
{ /*WARNING*/
  //Shutdown pins of VL53L0X ACTIVE-LOW-ONLY NO TOLERANT TO 5V will fry them
  pinMode(XSHUT_pin1, OUTPUT);
  pinMode(XSHUT_pin2, OUTPUT);
  
  Serial.begin(9600);
  
  Wire.begin();
  //Change address of sensor and power up next one
  
  pinMode(XSHUT_pin2, INPUT);
  delay(10);
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
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // LED NEOPIXEL
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
  int distance=Sensor1.readRangeContinuousMillimeters();
  int distance2=Sensor2.readRangeContinuousMillimeters();
  long capacitivesensorValue=capSensor.capacitiveSensor(30);

  Serial.print("Capteur1 " + (String)Sensor1.readRangeContinuousMillimeters());
  Serial.print(',');
  Serial.print("Capteur2 " + (String)Sensor2.readRangeContinuousMillimeters());
  Serial.println(',');
   photosensorValue = analogRead(photoSensorPin);
  if(photosensorValue < photothreshold && capacitivesensorValue > capacitivethreshold ) {
      forwardColorWipe(distanceToColor(distance));
  }
  else {
      forwardColorWipe(strip.Color(0, 0, 0));
}
  if(photosensorValue < photothreshold && capacitivesensorValue > capacitivethreshold ) {
     backwardColorWipe(distanceToColor(distance2));
  }
  else {
      backwardColorWipe(strip.Color(0, 0, 0));
}
} 

void forwardColorWipe(uint32_t c) {
  uint8_t begin_index = 6;
  uint8_t end_index = strip.numPixels();
  colorWipe(begin_index, end_index, c, 0);
}

void backwardColorWipe(uint32_t c) {
  uint8_t begin_index = 0;
  uint8_t end_index = 6;
  colorWipe(begin_index, end_index, c, 0);
}

uint32_t distanceToColor(int distance) {
  Serial.println("dist : " + distance);
  if(distance < 100) {
    return strip.Color(255, 0, 0);
  }

  if(distance < 500) {
    return strip.Color(204, 102, 0);
  }

  if(distance < 1000) {
    return strip.Color(0, 255, 0);
  }

  return strip.Color(0, 255, 0);
}

// Fill the dots one after the other with a color
void colorWipe(uint8_t begin_index, uint8_t end_index, uint32_t c, uint8_t wait) {
  for(uint16_t i=begin_index; i<end_index; i++) {
    strip.setPixelColor(i, c);
    strip.show();
    // delay(wait);
  }
}
