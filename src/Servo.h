#pragma once
#include <Arduino.h>

class Servo
{
public:
    Servo(uint8_t pin, int degree, bool activeState = HIGH);
    void move(int degree, uint32_t ms);
private:
    const uint8_t pin;
    int currentDegree;
    const bool activeState;
};