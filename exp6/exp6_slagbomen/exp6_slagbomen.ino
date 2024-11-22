#include <Arduino.h> // use of serial.print
#include <Servo.h> // working with servomotors

Servo servoMotor;
const int servoPin = 10; // pin D10 on an Arduino Nano board

void RotateServo(Servo servo, int maxRotation, bool direction) {
  if (direction) {
    for (int pos = 0; pos <= maxRotation; pos +=1) { // in steps of 1 degree
      servo.write(pos);
      Serial.print("positive rotation ");
      Serial.print(pos + "  ");
      delay(15); // waits 15ms to reach the position
    }
  } else {
    for (int pos = maxRotation; pos >= 0; pos -=1) { // in steps of 1 degree
      servo.write(pos);
      Serial.print("negative rotation ");
      Serial.print(pos + "  ");
      delay(15); // waits 15ms to reach the position
    }
  }
}

void setup() {
  Serial.begin(115200);
  servoMotor.attach(servoPin); // attaches the servo to pin D10
  int  pos = 0;
}

void loop() {
  RotateServo(servoMotor, 180, true); // roates from 0 degrees to 180 degrees
  RotateServo(servoMotor, 180, false); // roates from 180 degrees to 0 degrees
}