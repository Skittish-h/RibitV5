
#ifndef MOTOR_HPP
#define MOTOR_HPP
#include <Arduino.h>

class Motor
{
private:
    int8_t pinH;
    int8_t pinL;

    bool highPWM;
public:
    Motor(int8_t pinHigh, int8_t pinLow, bool isHighPWM);
    void setupMotor();
    void setSpeed(int speed);
};
#endif
