#include "Encoder.hpp"


Encoder::Encoder(int8_t iPin, int8_t pinB, int8_t hPin, int8_t lPin, bool isH) 
        : motor(hPin, lPin, isH), timeHist {0.0, 0.0, 0.0}
{

    intPin = iPin;
    bPin = pinB;
    Encoder::isH = isH;
    prevTime = 0;

    iterator = 0;

    targetTime = 0;
    
    prevError = 0;
    errorSum = 0;

    position = 0;
}

void Encoder::setUp() {
    pinMode(intPin, INPUT);
    pinMode(bPin, INPUT);
    motor.setupMotor();
}

float Encoder::controllLoop() {
    //elasped time as parameter only now due to debug prints
    float time = calculateElapsedTime(false);
    float posDiff;
    posDiff = getPosition();
    if(time < loopTime) {
        return 0.0;
    }
    nullPosition();
    time = calculateElapsedTime(posDiff != 0);
    addToTimeHist(time);

    time = getTimeVal();
    // Serial.print(time);
    if(posDiff == 0) {
        posDiff = 1;
    }
    float error = (time/posDiff) - targetTime;
    errorSum  = errorSum + error;
    if(errorSum > 2) {
        errorSum = 2;
    } else if (errorSum < -2) {
        errorSum = -2;
    }

    // Serial.println(errorSum);
    
    float output = kp*error + kd*(error-prevError)+ ki * errorSum;
    
    prevError = error;

    if(output>255) {
        output = 255;
    } else if (output < -255) {
        output = 255;
    }
    Serial.println(output);
    motor.setSpeed(int(output));
    return (time/posDiff);
}

void Encoder::addToTimeHist(float val) {
    timeHist[iterator] = val;
    iterator++;
    if (iterator > 2) {iterator  = 0;}
    
}

float Encoder::getTimeVal() {
    float total = 0;
    for (uint8_t i = 0; i < 3; i++)
    {
        total = total + timeHist[i];
    }

    return total/3.0;
    
}

void Encoder::encoderCallback() {
    // float timeElapsed = calculateElapsedTime();
    // distance of one tick is 10.05 / 30 = 0.335 (cm)
    // currentTime = timeElapsed;
    if (digitalRead(bPin) == isH) {
        position++;
    } else {
        position--;
    }
    
}



int32_t Encoder::getPosition() {
    int32_t pos2 = 0; 
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        pos2 = position;
    }
    return pos2;
}

void Encoder::nullPosition() {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        position=0;
    }
}

float Encoder::getElapsedTime() {
    float time = 0; 
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        time = currentTime;
    }
  return time;
}

float Encoder::getDistance() {
    int32_t pos = getPosition();

    return (pos/30.0) * 10.05;
}

void Encoder::setSpeed(float speed) {
    //save target time so we can save time later
    targetTime = (0.335/speed);
}
