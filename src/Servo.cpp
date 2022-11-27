#include "Servo.h"

namespace
{
#define MIN_SERVO_DEGREE 0.0
#define MAX_SERVO_DEGREE 180.0
#define MIN_SERVO_PULSE_IN_US 1000
#define MAX_SERVO_PULSE_IN_US 2000
#define SERVO_PERIOD_IN_US 20000
#define US_IN_MS 1000

constexpr auto SERVO_RANGE_DEGREE = MAX_SERVO_DEGREE - MIN_SERVO_DEGREE;
constexpr auto SERVO_RANGE_PULSE = MAX_SERVO_PULSE_IN_US - MIN_SERVO_PULSE_IN_US;
constexpr auto SERVO_PULSE_PER_DEGREE = SERVO_RANGE_PULSE / SERVO_RANGE_DEGREE;

inline void boundDegree(int& degree)
{
    if (degree < MIN_SERVO_DEGREE) degree = MIN_SERVO_DEGREE;
    if (degree > MAX_SERVO_DEGREE) degree = MAX_SERVO_DEGREE;
}
}

Servo::Servo(uint8_t pin, int degree, bool activeState) :
    pin(pin),
    currentDegree(degree),
    activeState(activeState)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, !activeState);
}

void Servo::move(int degree, uint32_t ms)
{
    const auto periods = (ms * US_IN_MS) / SERVO_PERIOD_IN_US;
    if (periods == 0)
        return;

    boundDegree(degree);
    const int deltaDegrees = degree - currentDegree;
    const auto deltaPulse = deltaDegrees * SERVO_PULSE_PER_DEGREE;
    const auto currentPulse = MIN_SERVO_PULSE_IN_US + currentDegree * SERVO_PULSE_PER_DEGREE;
    const auto pulsePerPeriod = deltaPulse / periods;

    for (uint32_t period = 1; period <= periods; period++)
    {
        const auto pulse = currentPulse + period * pulsePerPeriod;
        digitalWrite(pin, activeState);
        delayMicroseconds(pulse);
        digitalWrite(pin, !activeState);
        delayMicroseconds(SERVO_PERIOD_IN_US - pulse);
    }

    currentDegree = degree;
}