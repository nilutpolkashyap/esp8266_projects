// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "ASUS_X00TD";
char wifiPassword[] = "biscuitppp";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "329c1160-dbd4-11ea-883c-638d8ce4c23d";
char password[] = "d05a55ff15cc392dfb9ce76cf9595f29b8001fb1";
char clientID[] = "35b0a9e0-e905-11ea-b767-3f1a8f1211ba";

int obst = LOW;
int bstate = LOW;
float ldr_val = 0.0;

const int pushbtn = 5;
const int ir_sens = 16;
const int led = 4;
const int ldr = A0;

void setup()
{
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);

  pinMode(pushbtn, INPUT);
  pinMode(ir_sens, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(ldr, INPUT);
}

void loop()
{
  Cayenne.loop();

  bstate = digitalRead(pushbtn);
  if(bstate==HIGH)
  {
    Cayenne.virtualWrite(0,bstate,"digital_sensor","d");
  }
  else
  {
    Cayenne.virtualWrite(0,bstate,"digital_sensor","d");
  }

  obst = digitalRead(ir_sens);
  if(obst==HIGH)
  {
    Cayenne.virtualWrite(1,!obst,"digital_sensor","d");
  }
  else
  {
    Cayenne.virtualWrite(1,!obst,"digital_sensor","d");
  }

  ldr_val = analogRead(ldr);
  Cayenne.virtualWrite(3,ldr_val,"analog_sensor","null");
}

CAYENNE_IN(2)
{
  digitalWrite(4, getValue.asInt());
}
