#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7); 
//long echoPin = A1;
//long trigPin = A2;
long echoPin = 6;
long trigPin = 5;
int bzr = 13;
int led = A0;
//int led1 = D5;
long duration; 
long distance;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(bzr, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
//  pinMode(D5, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println("Memulai Membaca Jarak");
  delay(1000);
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds (10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print(distance);
//  lcd.print(" cm");
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
  if (distance > 15){
    digitalWrite(led, HIGH);
    digitalWrite(13, HIGH);
    tone(bzr, 700, 900);
  }else{
    digitalWrite(13, LOW);
    digitalWrite(led, LOW);
  }
}
