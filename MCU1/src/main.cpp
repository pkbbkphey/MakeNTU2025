
#include <Arduino.h>

#include "odrive.h"
#include "imu.h"
#include "balance_controller.h"

ODrive odrv;
MPU6050 imu;
balance_controller controller1;

void setup()
{
    Serial.begin(115200);

    odrv.initialize();
    imu.initialize();
    // imu.calibrate();     // This only needs to be done once for each MPU6050 unit
}

void loop()
{
    imu.update();
    float vel_out = controller1.balance_control(imu.angle_roll_buffer, micros());
    odrv.writeVel(vel_out);
}
