#include <Arduino.h> 
#include "WizGo.h"
#include <Wire.h>
#include "wizHuskyLens.h"
#include <VL53L0X.h>

WizGo wizGo;

VL53L0X DistanceSen;
uint16_t getDistance()
{
    if(DistanceSen.timeoutOccurred()== 0)
    {
        return DistanceSen.readRangeSingleMillimeters();
    }
    else 
    {
        return 0;
    }        
}


void setup()
{
  wizGo.init(1, 2, 3, 4);
  Wire.begin();
  wizHuskyLens.init();
  wizHuskyLens.setMode(4);
  DistanceSen.setAddress(0x27);
  DistanceSen.setTimeout(500);
  DistanceSen.init();
  DistanceSen.setSignalRateLimit(0.1);
  DistanceSen.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  DistanceSen.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);

}

void loop()
{
  wizHuskyLens.read();
  
  if(((getDistance())<(80))&&(wizGo.customFound2()))
  {
    wizGo.runPreset(2, 2);
    delay(0.05*1000);
  
  }else{
    
    if(wizGo.isFoundX(0, 0))
    {
      
      if(wizGo.isFoundX(3, 0))
      {
        wizGo.defence(getDistance());
      
      }else{
        
        if(wizGo.isFoundX(2, 0))
        {
          wizGo.chase(0, 750);
          
          if((getDistance())<(80))
          {
            wizGo.runPreset(0, 3);
            delay(0.2*1000);
            wizGo.runPreset();
            delay(0.5*1000);
          
          }
        
        }else{
          wizGo.chase(0, 750);
        
        }
      
      }
    
    }else{
      wizGo.randomWalk(0);
      delay(0.05*1000);
    
    }
  
  }

}
