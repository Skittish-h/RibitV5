#ifndef LINESENS_H
#define LINESENS_H
#include <Arduino.h>


class LineSens
{
private:
    int DIN, DOUT, SCK, EN;
    int lastPos;

    

public:
    uint16_t maxVals[8];
    uint16_t minVals[8];

    LineSens(int din, int dout, int sck, int en);
    
    int getRawData(int sens);

    void calibrate();
    int getLine();
};
#endif
