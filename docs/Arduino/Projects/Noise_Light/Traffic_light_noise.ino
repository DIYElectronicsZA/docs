#include <Adafruit_NeoPixel.h>
#define PIN 6
#define buzz 4
#define NUMPIXELS 3
#include "RunningAverage.h"

RunningAverage myRA(20);
int samples = 0;
int sensorValue, caseCount;
int Run_ave;
  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup () 
{
  Serial.begin (9600);
  pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
  myRA.clear();
  pixels.begin();
}
void loop () 
{
  sensorValue = analogRead(A0);
  myRA.addValue(sensorValue);
  Run_ave = (myRA.getAverage());
  samples++;
  Serial.print("Running Average: ");
  Serial.println(Run_ave);
  Serial.println("Reading:");

  if (sensorValue > Run_ave + 8)
    {
      Serial.println(sensorValue);
      pixels.setPixelColor(0, pixels.Color(0,0,0));
      pixels.setPixelColor(1, pixels.Color(0,0,0));
      pixels.setPixelColor(2, pixels.Color(255,0,0));
      digitalWrite(buzz, HIGH);
      pixels.show();
      delay(1000);
    }
  else if (sensorValue > Run_ave + 3)
    {
      pixels.setPixelColor(0, pixels.Color(0,0,0));
      pixels.setPixelColor(1, pixels.Color(255,165,0));
      pixels.setPixelColor(2, pixels.Color(0,0,0));
      digitalWrite(buzz, LOW);
      pixels.show();
      delay(1500);
    }
   else {
    pixels.setPixelColor(0, pixels.Color(0,255,0));
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(2, pixels.Color(0,0,0));
    digitalWrite(buzz, LOW);
    pixels.show();
   }
  if (samples == 300)
  {
    samples = 0;
    myRA.clear();
  }
  delay(100);
//  sensorValue = analogRead(A0);
//  Serial.println(sensorValue);
//  if(sensorValue < 300){
//    pixels.setPixelColor(0, pixels.Color(0,255,0));
//    pixels.setPixelColor(1, pixels.Color(0,0,0));
//    pixels.setPixelColor(2, pixels.Color(0,0,0));
//    digitalWrite(buzz, LOW);
//  }
//  if(sensorValue > 300 && sensorValue < 320){
//    pixels.setPixelColor(0, pixels.Color(0,0,0));
//    pixels.setPixelColor(1, pixels.Color(255,165,0));
//    pixels.setPixelColor(2, pixels.Color(0,0,0));
//    digitalWrite(buzz, LOW);
//  }
//  if(sensorValue > 320){
//    pixels.setPixelColor(0, pixels.Color(0,0,0));
//    pixels.setPixelColor(1, pixels.Color(0,0,0));
//    pixels.setPixelColor(2, pixels.Color(255,0,0));
//    digitalWrite(buzz, HIGH);
//    pixels.show();
//    delay(1000);
//  }
//  pixels.show();
//  delay(100);
  
}
