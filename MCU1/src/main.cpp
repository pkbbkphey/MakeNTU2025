
#include <Arduino.h>

#define DBG
#include "odrive.h"
#include "imu.h"

ODrive odrv;
MPU6050 imu;

void setup()
{
    #ifdef DBG
    Serial.begin(115200);
    #endif

    odrv.initialize();
    imu.initialize();
}

void loop()
{
    imu.update();

    odrv.writeVel(1);    
}
