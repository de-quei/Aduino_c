#include <Arduino.h> 
#include <Wire.h>
#include "wizHuskyLens.h"


void DcMotorControl(uint8_t MotNum, uint8_t CwCcw, int Speed)
{
    if(MotNum)      //-- right
    {
        if(CwCcw)   //-- Clockwise
        {
            ledcDetachPin(33);
            pinMode(33, OUTPUT);
            digitalWrite(33, LOW);
            
            ledcSetup(8, 5000, 10); 
            ledcAttachPin(32, 8);
            ledcWrite(8, Speed);
        }
        else        //-- CCW
        {
            ledcDetachPin(32);
            pinMode(32, OUTPUT);
            digitalWrite(32, LOW);
            
            ledcSetup(9, 5000, 10); 
            ledcAttachPin(33, 9);
            ledcWrite(9, Speed);
        }
    }
    else            //-- Left
    {
        if(CwCcw)   //-- Clockwise
        {
            ledcDetachPin(14);
            pinMode(14, OUTPUT);
            digitalWrite(14, LOW);
            
            ledcSetup(0, 5000, 10); 
            ledcAttachPin(13, 0);
            ledcWrite(0, Speed);
        }
        else        //-- CCW
        {
            ledcDetachPin(13);
            pinMode(13, OUTPUT);
            digitalWrite(13, LOW);
            
            ledcSetup(1, 5000, 10); 
            ledcAttachPin(14, 1);
            ledcWrite(1, Speed);
        }
    }
}


void setup()
{
  Wire.begin();
  wizHuskyLens.init();
  wizHuskyLens.setMode(3);

}

void loop()
{
  wizHuskyLens.read();
  
  if((wizHuskyLens.getArrowInfo(1,0))>(160))
  {
    DcMotorControl(0, 1, 450);
    DcMotorControl(1, 1, 150);
  
  }else{
    
    if((wizHuskyLens.getArrowInfo(1,0))<(160))
    {
      DcMotorControl(0, 0, 200);
      DcMotorControl(1, 0, 450);
    
    }else{
      DcMotorControl(0, 1, 350);
      DcMotorControl(1, 0, 350);
    
    }
  
  }

}
