#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

Servo myservo;

int trigPin = D1;
int echoPin = D2;
int ledmerah = D7;
int ledhijau = D8;

long duration;
int distance;

LiquidCrystal_I2C lcd(0x27, 10, 2);
int SDA_pin = D5;
int SCL_pin = D6;

void setup() {
  pinMode(ledmerah, OUTPUT);
  pinMode(ledhijau, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myservo.attach(D4);
  Wire.begin(SDA_pin, SCL_pin);
  lcd.init();
  lcd.backlight();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin,HIGH);
  distance = 0.034 * duration / 2;
  Serial.print("Jarak :");
  Serial.print(distance);
  Serial.print(" cm\n");

  if(distance<=10){
    digitalWrite(ledhijau,HIGH);
    digitalWrite(ledmerah,LOW);
    myservo.write(180);
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print(distance);
    lcd.print(" cm");
    lcd.setCursor(0,1);
    lcd.print("Terbuka");
  }else{
    digitalWrite(ledmerah,HIGH);
    digitalWrite(ledhijau,LOW);
    myservo.write(0);
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print(distance);
    lcd.print(" cm");
    lcd.setCursor(0,1);
    lcd.print("Tertutup");
  }

  delay(1000);
}