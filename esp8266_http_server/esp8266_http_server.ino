#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi credentials
const char* WIFI_SSID = "***SSIDNAME***";
const char* WIFI_PASS = "***PASSWORD***";

// Web server running on port 80
ESP8266WebServer server(80);

const int LED_PIN = 2; // For onboard LED on NodeMCU

// Handle turning LED on
void handleLedOn() {
  digitalWrite(LED_PIN, HIGH);  // Turn on LED
  server.send(200, "text/plain", "LED is ON");
}

// Handle turning LED off
void handleLedOff() {
  digitalWrite(LED_PIN, LOW);   // Turn off LED
  server.send(200, "text/plain", "LED is OFF");
}

void setup() {
  // Start Serial communication
  Serial.begin(115200);
  Serial.println();

  // Configure LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Ensure LED is off at start

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(WiFi.localIP());

  // Define routes for turning LED on and off
  server.on("/ledon", handleLedOn);
  server.on("/ledoff", handleLedOff);

  // Start the web server
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}