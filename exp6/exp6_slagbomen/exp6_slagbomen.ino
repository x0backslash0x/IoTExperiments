#include <Arduino.h> // use of serial.print
#include <Servo.h> // working with servomotors

enum Action {
  CLOSE, // 0
  OPEN // 1
};

Servo servoMotor;
const int servoPin = 10; // pin D10 on an Arduino Nano board
const int degrees = 180;
const int SW = 5; // pin D5 on an Arduino Nano board
Action previousAction = CLOSE;

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
  pinMode(SW, INPUT);
  int pos = 0;
}

void loop() {
  if (digitalRead(SW) == 0) {
    RotateServo(servoMotor, degrees, previousAction);

    switch (previousAction) {
      case CLOSE:
        previousAction = OPEN; // rotate counter-clockwise
        break;
      case OPEN:
        previousAction = CLOSE; // rotate clockwise
        break;
    }
  }
}