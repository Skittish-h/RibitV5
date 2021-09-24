#include "Motor.hpp"

Motor::Motor(int8_t pinHigh, int8_t pinLow, bool isHighPWM) {
    //pinHigh is the pin that must be set high to move forewards
    pinH = pinHigh;
    //pinLow must be set low to go forewards
    pinL = pinLow;
    //bool that checks if the high pin is the PWM pin
    highPWM = isHighPWM;
}

void Motor::setupMotor() {
    // just set pin modes
    pinMode(pinH, OUTPUT);
    pinMode(pinL, OUTPUT);
}

void Motor::setSpeed(int speed) {
    //given a value from -255 to 255 applie that shit to the motor
    if(speed > 255) {
        speed = 255;
    } 
    else if (speed < -255)
    {
        speed = -255;
    }
    
    //boring if statements
    if (speed > 0) {
        switch (highPWM)
        {
        case true:
            analogWrite(pinH, speed);
            digitalWrite(pinL, LOW);
            break;
        
        default:
            analogWrite(pinL, 255 - speed);
            digitalWrite(pinH, HIGH);
            break;
        }
    } else {
        switch (highPWM)
        {
        case true:
            analogWrite(pinH, 255 + speed);
            digitalWrite(pinL, HIGH);
            break;
        
        default:
            analogWrite(pinL, - speed);
            digitalWrite(pinH, LOW);
            break;
        }
    }
    
}