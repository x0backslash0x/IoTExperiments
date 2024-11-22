#include <Arduino.h> // use of serial.print
#include <Servo.h> // working with servomotors

Servo servoMotor;
const int servoPin = 10; // pin D10 on an Arduino Nano board

void setup() {
  Serial.begin(115200);
  servoMotor.attach(servoPin); // attaches the servo to pin D10
  int  pos = 0;
}

void loop() {
  // roates from 0 degrees to 180 degrees
  for (int pos = 0; pos <= 180; pos +=1) { // in steps of 1 degree
    servoMotor.write(pos);
    Serial.print("positive rotation ");
    Serial.print(pos + "  ");
    delay(15); // waits 15ms to reach the position
  }

  // rotates from 180 degrees to 0 degrees
  for (int pos = 180; pos >= 0; pos -=1) { // in steps of 1 degree
    servoMotor.write(pos);
    Serial.print("negative rotation ");
    Serial.print(pos + "  ");
    delay(15); // waits 15ms to reach the position
  }
}