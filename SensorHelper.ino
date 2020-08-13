#include <NewPing.h>
#include <LiquidCrystal.h>
#include <TonePlayer.h>

const int piezoPin = 9;
const int trigPin = 10;
const int echoPin = 11;
const int MAX_DISTANCE = 400;
const int MIN_THRESHOLD = 100;
const int MAX_THRESHOLD = 300;
int buttonCurrent;
int buttonPrevious = LOW;
const int button = 13;
const int INITIAL_DELAY = 60000;

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
LiquidCrystal lcd(12, 6, 5, 4, 3, 2);
TonePlayer tone1 (TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L); 

//4th pin,6th pin,

float duration, distance;

void setup() {
  pinMode(button, INPUT);
  pinMode(piezoPin, OUTPUT);
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop() {
  Serial.print(digitalRead(button));
  delay(50);
  duration = sonar.ping();
  distance = (duration/2) * 0.0343;
  if(distance <= MAX_THRESHOLD && distance >= MIN_THRESHOLD) {
    play();
  }
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm");
  delay(350);
  lcd.clear();
}

void play() {
  tone1.tone (220);  // 220 Hz
  delay (500);
  tone1.noTone ();
  tone1.tone (440);
  delay (500);
  tone1.noTone ();
  tone1.tone (880);
  delay (500);
  tone1.noTone ();
 
}
