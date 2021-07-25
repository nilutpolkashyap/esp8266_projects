#include <Servo.h> // including servo library.

int speakerPin = 9;
int length = 26; // the number of notes
char notes[] = "aabacdaabaecaahfcndbggfcec "; // a space represents a rest
int beats[] = {2,2,4,4,4,8,2,2,4,4,4,8,2,2,4,4,4,4,0,4,3,1,4,4,4,8,16 };
int tempo = 75; 

int servoPin = 10;
int buzzerPin = 11;
int musicPin = 3;
int surprisePin = 4;

int music = 0;
int surprise = 0;


Servo servo_1;

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
void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(musicPin, INPUT);
  pinMode(surprisePin, INPUT);
  servo_1.attach(0);
  servo_1.write (0);
}
void loop() {
  music = digitalRead(musicPin);
  surprise = digitalRead(surprisePin);
  
  if(music == 1){
    for (int i = 0; i < length; i++) 
    {
      if (notes[i] == ' ') 
      {
        delay(beats[i] * tempo); // rest
      }
      else {
        playNote(notes[i], beats[i] * tempo);
        // pause between notes
        
        if(notes[i+1] != 'n')
        { 
          delay(tempo );
        }
        else 
        {
          i += 1;
        }
      }
    }
  }
  if(music == 0)
  {
    digitalWrite(speakerPin, LOW);
  }

  if(surprise == 1)
  {
    servo_1.write (0);
  }
  if(surprise == 0)
  {
    servo_1.write (90);
  }

  
}
