#include "LineSens.hpp"

LineSens::LineSens(int din, int dout, int sck, int en) :
    minVals{4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095}, 
    maxVals {0, 0, 0, 0, 0, 0, 0, 0},
    DIN{din}, DOUT {dout}, SCK{sck}, EN{en}
{


    pinMode(EN, OUTPUT);
    pinMode(DOUT, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(DIN, INPUT);

    digitalWrite(EN,HIGH); 
    digitalWrite(DOUT,LOW); 
    digitalWrite(SCK,LOW);    

}
int LineSens::getLine() {
    
    uint16_t sensorValues[8];
    
    uint32_t avg = 0;
    uint16_t sum = 0;
    
    bool isLine = false;
    //get data
    for (uint8_t i = 0; i < 8; i++)
    {
        sensorValues[i] = getRawData(i);
    }
    
    for (uint8_t i = 0; i < 8; i++)
    {
        uint16_t denom = maxVals[i] - minVals[i];
        int16_t value = (((int32_t)sensorValues[i]) - minVals[i]) * 1000 / denom;
        
        if (value < 0) {value = 0;}
        if (value > 1000) {value = 1000;}

        value = 1000-value;
        if(value > 200) 
        {
            isLine = true;
        }
        if (value > 50)
        {
            avg += (uint32_t)value * (i * 1000);
            sum += value;
        }
    }
    if (!isLine)
    {
        if(lastPos > 3500) 
        {
            return 7000;
        }
        else 
        {
            return 0;
        }
    }
    


    lastPos = avg / sum;
    return avg / sum;
}



void LineSens::calibrate() {
    uint16_t tempMax[] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint16_t tempMin[] = {4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095};
    
    //set temporary maxes and mins during 10 measurements
    for(uint8_t j = 0; j < 10; j++) 
    {
        for (uint8_t i = 0; i < 8; i++)
        {
            uint16_t value = getRawData(i);
            if((j == 0) || (value < tempMin[i])) {
                tempMin[i] = value;
            } 
            if((j == 0) || (value > tempMax[i])) 
            {
                tempMax[i] = value;
            }
        }
    }

    //if all vals are lower or higher set new normal
    for (uint8_t i = 0; i < 8; i++)
    {
        if (tempMin[i] > maxVals[i])
        {
            maxVals[i] = tempMin[i];
        }
        if (tempMax[i] < minVals[i])
        {
            minVals[i] = tempMax[i];
        }
        
    }
    
    
}


int LineSens::getRawData(int sens){
    int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)
  sens++;
  //allow channel selection
  commandbits|=((sens-1)<<3);

  digitalWrite(EN,LOW);
  
  for (int i=7; i>=3; i--){
    digitalWrite(DOUT,commandbits&1<<i);
    //cycle clock
    digitalWrite(SCK,HIGH);
    digitalWrite(SCK,LOW);    
  }

  digitalWrite(SCK,HIGH);    //ignores 2 null bits
  digitalWrite(SCK,LOW);
  digitalWrite(SCK,HIGH);  
  digitalWrite(SCK,LOW);

  //read bits from adc
  for (int i=11; i>=0; i--)  {
    adcvalue+=digitalRead(DIN)<<i;
    //cycle clock
   
    digitalWrite(SCK,HIGH);
    digitalWrite(SCK,LOW);
  }
  digitalWrite(EN, HIGH); //turn off device
  return adcvalue;
}