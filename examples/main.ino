#include <Servo.h>
#include <Arduino.h>

#define SERVO_PIN 3
#define OFF_DEGREE 80
#define ON_DEGREE 150
#define MOVE_TIME_IN_MS 1000

Servo servo(SERVO_PIN, OFF_DEGREE);

void setup() {
}

void loop() {
    servo.move(ON_DEGREE, MOVE_TIME_IN_MS);
    servo.move(OFF_DEGREE, MOVE_TIME_IN_MS);
}