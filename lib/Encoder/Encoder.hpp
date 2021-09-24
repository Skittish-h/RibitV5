#ifndef ENCODER_HPP
#define ENCODER_HPP
#include <Arduino.h>
#include <util/atomic.h>
#include <Motor.hpp>


class Encoder
{
private:
    int8_t intPin;
    int8_t bPin;

    float kp = 60000.0;
    float kd = 1.0;
    float ki = 30.0;
    

    float timeHist[5];


    static constexpr float loopTime = 0.05;
    
    volatile float currentTime;

    float prevError;
    float errorSum;

    bool isH;

    long prevTime;

    int iterator;

    volatile int32_t position;
    // volatile ;

    float calculateElapsedTime(bool reset) {
        // distance of one tick is 10.05 / 30 = 0.335 (cm)
        long timeNow = micros();
        float timeElapsed = ((float) (timeNow - prevTime))/( 1.0e6 );
        
        if (reset) {
            prevTime = timeNow;
        }
        

        return timeElapsed;
    }

public:
    float targetTime;
    Motor motor;

    Encoder(int8_t iPin, int8_t pinB, int8_t hPin, int8_t lPin, bool isH) ;
    
    void setUp();
    void encoderCallback();
    void setSpeed(float speed);
    void addToTimeHist(float val);
    float getTimeVal();

    float controllLoop();
    void nullPosition();

    float getElapsedTime();
    
    int32_t getPosition();
    float getDistance();
};




#endif
