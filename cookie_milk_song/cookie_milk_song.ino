/*
Hackathon v2. Christmas edition. Cookie and milk dispensing with pumop and continuous servo.
*/
#include <Servo.h>  // servo library

Servo servo1;  // servo control object

int angle_speed;
int STOP_SERVO = 90;

const int button1Pin = 2;
const int button2Pin = 3;
const int buzzerPin = 10;
const int pumpPin = 11;
const int ledPin =  13;

int button1State, button2State;  // variables to hold the pushbutton states
//Generic song
int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
/*
// Christmas song
int length = 29;
char notes[] = "faagfvvagaCCbCaDCvagfeagffef ";//Chirstmas song
int beats[] = { 2,3,1,2,2,2,2,2,2,2,2,2,2,6,2,3,1,2,2,2,2,2,2,2,2,2,2,6,2 };
*/
int tempo = 150;  // The tempo is how fast to play the song (beats per second).

void setup()
{
  servo1.attach(9, 900, 2100);
  Serial.begin(9600);

  // Set up the pins to be an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  // Set up the pins to be an output:
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);  // sets the buzzer pin as an OUTPUT
  pinMode(pumpPin, OUTPUT); // sets the pump pin as en OUTPUT

  Serial.println("Welcome to the hackathon v2 christmas special!");
  Serial.println("If we identify santa though visual recognition he will receive a treat.");
  Serial.println();  // Print a blank line
}


void loop()
{
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  if (((button1State == LOW) && (button2State == HIGH)) || ((button1State == HIGH) && (button2State == LOW))) {
    digitalWrite(ledPin, HIGH);  // turn the LED on
    continuous_servo(); // Dispense cookie.
    pour_milk(); // Dispense milk.
    play_chirstmas_song(); // Play song
  } else {
    digitalWrite(ledPin, LOW);  // turn the LED off
  }
}

void play_tone(int tone, int duration)
{
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(tone);
  }
}

void play_note(char note, int duration)
{
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      play_tone(tones[i], duration);
    }
  }
}

void play_chirstmas_song()
{
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ')
      delay(beats[i] * tempo); // rest
    else
      play_note(notes[i], beats[i] * tempo);
    // pause between notes
    delay(tempo / 2);
  }
}

void continuous_servo( )
{
  int speed;
  angle_speed = 180; //Max speed on servo
  Serial.print("Setting angle_speed to ");
  Serial.println(angle_speed);

  servo1.write(angle_speed);   // Clockwise movement from 110 -> 180. Deadzone from 91 -> 110
  delay(4200);    // Pause to get it time to move. Moves 1,5cm/sec.
  servo1.write(180-angle_speed);     // Countercockwise movement from 0->89.
  delay(4100);    // Pause to get it time to move. Mechanical gearing issues require custom calibration.
  //STOP
  servo1.write(STOP_SERVO);
}

void pour_milk()
{
    digitalWrite(pumpPin, HIGH);
    delay(5000);
    digitalWrite(pumpPin, LOW);
}
