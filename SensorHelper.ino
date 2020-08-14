#include <NewPing.h>
#include <LiquidCrystal.h>
#include <TonePlayer.h>

#define LCD_LIGHT_PIN A0

const int buttonPin = 8;
const int piezoPin = 9; //should be 5
const int trigPin = 10;
const int echoPin = 11;  
const int MAX_DISTANCE = 400;
const int MIN_THRESHOLD = 100;
const int MAX_THRESHOLD = 300;
int buttonState;
int previousButtonState;
bool previousActive = true;
bool isActive = false;
int loopCount = 0;
const int INITIAL_DELAY = 60;

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
LiquidCrystal lcd(12, 6, 5, 4, 3, 2);
TonePlayer tone1 (TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L); 

//4th pin,6th pin,

float duration, distance;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(piezoPin, OUTPUT);
  pinMode(LCD_LIGHT_PIN, OUTPUT);
  digitalWrite(LCD_LIGHT_PIN, LOW);
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop() {
  safeUpdate();
  if(isActive) {
    digitalWrite(LCD_LIGHT_PIN, HIGH);
    if(previousActive != isActive) {
      for(int i = INITIAL_DELAY * 100; i >= 0; i--) {
        if(i % 100 == 0) {
           lcd.clear();
           lcd.print(i/100);
           lcd.print(" SECONDS...");
        }
        delay(10);
        safeUpdate();
        if(!isActive) {
          break;
        }
      }
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("ACTIVE");
    }
    previousActive = true;
    duration = sonar.ping();
    distance = (duration/2) * 0.0343;
    if(distance <= MAX_THRESHOLD && distance >= MIN_THRESHOLD) {
      play();
      isActive = false;
    }
  } 
  else {
    if(isActive != previousActive) {
       digitalWrite(LCD_LIGHT_PIN, LOW);
       lcd.clear();
       lcd.setCursor(3,0);
       lcd.print("NOT ACTIVE");
    }
    previousActive = false;
  }
  
}

void safeUpdate() {
  buttonState = digitalRead(buttonPin);
  if(previousButtonState != buttonState) {
    updateActive();
  }
  previousButtonState = buttonState;
}

void updateActive() {
  if(buttonState == 1) {
    isActive = !isActive;
  }
}

void play() {
  tone1.tone (220);  // 220 Hz
  updateActive();
  delay (500);
  updateActive();
  tone1.noTone ();
  tone1.tone (440);
  delay (500);
  updateActive();
  tone1.noTone ();
  tone1.tone (880);
  delay (500);
  updateActive();
  tone1.noTone ();
 
}
