#include<Servo.h>
Servo myServo;

const int piezo = A0;
const int switchPin = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int redLed = 5;
int knockVal;
int switchVal;
const int quiteKnock = 100;
const int loudKnock = 1000;
const int timebetween_knocks = 1000;
unsigned long previousTime = 0;
boolean locked = false;
int numberOfKnocks = 0;

void setup() {
  myServo.attach(9);
  pinMode(yellowLed,OUTPUT);
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(switchPin,INPUT);
  Serial.begin(9600);
  digitalWrite(greenLed,HIGH);
  myServo.write(0);
  Serial.println("The box is unlocked");
}

void loop() {
  if(locked == false) {
    switchVal = digitalRead(switchPin);
    if(switchVal == HIGH){
      locked = true;
      digitalWrite(greenLed,LOW);
      digitalWrite(redLed,HIGH);
      myServo.write(90);
      Serial.println("The box is locked");
      numberOfKnocks = 0;
      delay(1000);
    }
  }
  if(locked == true) {
    knockVal = analogRead(piezo);
    unsigned currentTime = millis();
    if(numberOfKnocks == 0) {
      previousTime = currentTime;
    }
    if(numberOfKnocks < 3 && knockVal >0) {
      if(checkForKnock(knockVal) == true) {
        if(currentTime - previousTime < timebetween_knocks){
          numberOfKnocks++;
          previousTime = currentTime;
        }
      }
    }
    if(currentTime - previousTime > timebetween_knocks) {
      numberOfKnocks = 0;
      Serial.println("Knocking failed");
      digitalWrite(redLed,LOW);
      digitalWrite(greenLed,HIGH);
      delay(300);
      digitalWrite(greenLed,LOW);
      digitalWrite(yellowLed,HIGH);
      delay(300);
      digitalWrite(yellowLed,LOW);
      digitalWrite(redLed,HIGH);
    }
    if(numberOfKnocks >=3) {
      locked = false;
      myServo.write(0);
      delay(20);
      digitalWrite(greenLed,HIGH);
      digitalWrite(redLed,LOW);
      Serial.println("The box is unlocked");
    }
  }
}

boolean checkForKnock(int value) {
  if(value > quiteKnock && value < loudKnock) {
      digitalWrite(yellowLed,HIGH);
      delay(50);
      digitalWrite(yellowLed,LOW);
      Serial.print("Knock #: ");
      Serial.println(1+numberOfKnocks);
      return true;
  }
  else {
      return false;
  }
}
