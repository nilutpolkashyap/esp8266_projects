#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "ASUS_X00TD";
const char* password = "biscuitppp";

// Initialize Telegram BOT
#define BOTtoken "1389621433:AAHwNwwQs4C1thPVwQN2rpj7u3HIeVS0-EU"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "1222668331"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int lightPin = D3;
const int candlePin = D4;
const int surprisePin = D8;
const int speakerPin = D7;
bool ledState = LOW;


int length = 26; // the number of notes
char notes[] = "aabacdaabaecaahfcndbggfcec "; // a space represents a rest
int beats[] = {2,2,4,4,4,8,2,2,4,4,4,8,2,2,4,4,4,4,0,4,3,1,4,4,4,8,16 };
int tempo = 75;

void playTone(int tone, int duration) {
for (long i = 0; i < duration * 1000L; i += tone * 2) {
digitalWrite(speakerPin, HIGH);
delayMicroseconds(tone);
digitalWrite(speakerPin, LOW);
delayMicroseconds(tone);
}
}
void playNote(char note, int duration) {
char names[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
int tones[] = { 1515, 1351, 1136, 1205, 1012, 903, 852, 759 };
// play the tone corresponding to the note name
for (int i = 0; i < 8; i++) {
if (names[i] == note) {
playTone(tones[i], duration);
}
}
}



// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands to control the IOT BirthDay CAKE.\n\n";
      welcome += "/light_on to turn LIGHTS ON \n";
      welcome += "/light_off to turn LIGHTS OFF \n";
      welcome += "/light_state to request current LIGHTS state \n";
      
      welcome += "/candle_on to turn CANDLES ON \n";
      welcome += "/candle_off to turn CANDLES OFF \n";
      welcome += "/candle_state to request current CANDLES state \n";
      
      welcome += "/surprise_on to open SURPRISE BOX \n";
      welcome += "/surprise_off to close SURPRISE BOX \n";
      welcome += "/surprise_state to request current SURPRISE BOX state \n";
      
      welcome += "/music_on to play SONG\n";
      welcome += "/music_off to stop SONG \n";
      welcome += "/music_state to request current SONG state \n";
      bot.sendMessage(chat_id, welcome, "");
    }



    if (text == "/light_on") {
      bot.sendMessage(chat_id, "LIGHTS TURNED ON", "");
      ledState = HIGH;
      digitalWrite(lightPin, ledState);
    }
    
    if (text == "/light_off") {
      bot.sendMessage(chat_id, "LIGHTS TURNED OFF", "");
      ledState = LOW;
      digitalWrite(lightPin, ledState);
    }
    
    if (text == "/light_state") {
      if (digitalRead(lightPin)){
        bot.sendMessage(chat_id, "LIGHTS ARE ON", "");
      }
      else{
        bot.sendMessage(chat_id, "LIGHTS ARE OFF", "");
      }
    }



    if (text == "/candle_on") {
      bot.sendMessage(chat_id, "CANDLES TURNED ON", "");
      ledState = HIGH;
      digitalWrite(candlePin, ledState);
    }
    
    if (text == "/candle_off") {
      bot.sendMessage(chat_id, "CANDLES TURNED OFF", "");
      ledState = LOW;
      digitalWrite(candlePin, ledState);
    }
    
    if (text == "/candle_state") {
      if (digitalRead(candlePin)){
        bot.sendMessage(chat_id, "CANDLES ARE ON", "");
      }
      else{
        bot.sendMessage(chat_id, "CANDLES ARE OFF", "");
      }
    }


    

    if (text == "/surprise_on") {
      bot.sendMessage(chat_id, "SURPRISE BOX OPENED", "");
      ledState = HIGH;
      digitalWrite(surprisePin, ledState);
    }
    
    if (text == "/surprise_off") {
      bot.sendMessage(chat_id, "SURPRISE BOX CLOSED", "");
      ledState = LOW;
      digitalWrite(surprisePin, ledState);
    }
    
    if (text == "/surprise_state") {
      if (digitalRead(surprisePin)){
        bot.sendMessage(chat_id, "SURPRISE BOX IS OPEN", "");
      }
      else{
        bot.sendMessage(chat_id, "SURPRISE BOX IS CLOSED", "");
      }
    }


    

    if (text == "/music_on") {
      bot.sendMessage(chat_id, "MUSIC state set to ON", "");
      ledState = HIGH;
      digitalWrite(speakerPin, ledState);
    }
    
    if (text == "/music_off") {
      bot.sendMessage(chat_id, "MUSIC state set to OFF", "");
      ledState = LOW;
      digitalWrite(speakerPin, ledState);
    }
    
    if (text == "/music_state") {
      if (digitalRead(speakerPin)){
        bot.sendMessage(chat_id, "MUSIC is ON", "");
      }
      else{
        bot.sendMessage(chat_id, "MUSIC is OFF", "");
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  #ifdef ESP8266
    client.setInsecure();
  #endif


  pinMode(lightPin, OUTPUT);
  digitalWrite(lightPin, ledState);
  pinMode(candlePin, OUTPUT);
  digitalWrite(candlePin, ledState);
  pinMode(surprisePin, OUTPUT);
  digitalWrite(surprisePin, ledState);
  pinMode(speakerPin, OUTPUT);
  //digitalWrite(ledPin4, ledState);
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
