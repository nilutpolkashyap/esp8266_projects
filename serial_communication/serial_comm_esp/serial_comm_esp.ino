#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

ESP8266WebServer server(80);
SoftwareSerial s(D6, D5);

const char* ssid = "wifi_ssid";
const char* password = "password";

int data;
String page = "";

void setup()
{
  s.begin(9600);
  Serial.begin(9600);

  Serial.println("Connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.....!");
  Serial.println("Got IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("HTTP server started");

  server.on("/", [](){
    page = "<h1>Sensor to Node MCU Web Server</h1><h3>Data:</h3> <h4>"+String(data)+"</h4>";
    server.send(200, "text/html", page);
  });
}

void loop()
{
  s.write("s");

  if(s.available()>0)
  {
    data = s.read();
    Serial.println(data);
  }
//  delay(1000);
  server.handleClient();
}
