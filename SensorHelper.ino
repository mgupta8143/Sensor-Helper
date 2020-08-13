#include <NewPing.h>
#include <LiquidCrystal.h>

const int trigPin = 10;
const int echoPin = 11;
const int MAX_DISTANCE = 400;

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);
LiquidCrystal lcd(12, 9, 5, 4, 3, 2);

//4th pin,6th pin,

float duration, distance;

void setup() {
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop() {
  delay(50);
  duration = sonar.ping();
  distance = (duration/2) * 0.0343;
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm");
  delay(350);
  lcd.clear();
  

}
