#include <SoftwareSerial.h>
SoftwareSerial s(5,6);

const int potpin = A0;
int potvalue;

void setup()
{
  s.begin(9600);  
  Serial.begin(9600);
  pinMode(potpin, INPUT);
}

void loop()
{
  potvalue = analogRead(potpin);
  potvalue = map(potvalue, 0, 1023, 0, 255);
  Serial.println(potvalue);
  if(s.available()>0)
  {
    s.write(potvalue);
  }
  delay(100);
}
