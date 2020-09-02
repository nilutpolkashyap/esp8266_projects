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
char clientID[] = "0a8a2f30-e7b0-11ea-b767-3f1a8f1211ba";

int obst = HIGH;

void setup()
{
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  pinMode(5, INPUT);
}

void loop()
{
  Cayenne.loop();

  obst = digitalRead(5);
  if(obst==HIGH)
  {
    Cayenne.virtualWrite(1,obst,"digital_sensor","d");
  }
  else
  {
    Cayenne.virtualWrite(1,obst,"digital_sensor","d");
  }
}

CAYENNE_IN(0)
{
  digitalWrite(2, !getValue.asInt());

  
}
