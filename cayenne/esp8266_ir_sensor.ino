// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 

#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "SSID_NAME";
char wifiPassword[] = "password";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "329c1160-dbd4-11ea-883c-638d8ce4c23d";
char password[] = "d05a55ff15cc392dfb9ce76cf9595f29b8001fb1";
char clientID[] = "35b0a9e0-e905-11ea-b767-3f1a8f1211ba";

int obst = LOW;

const int ir_sens = D1;

void setup()
{
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);

  pinMode(ir_sens, INPUT);
  Serial.begin(115200);
}

void loop()
{
  Cayenne.loop();

  obst = digitalRead(ir_sens);
  if(obst==HIGH)
  {
    Cayenne.virtualWrite(2,!obst,"digital_sensor","d");
    Serial.println("YES");
  }
  else
  {
    Cayenne.virtualWrite(2,!obst,"digital_sensor","d");
    Serial.println("NO");
  }
}
