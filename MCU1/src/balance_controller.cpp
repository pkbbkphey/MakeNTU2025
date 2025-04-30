
#include <Arduino.h>
#include "balance_controller.h"

float balance_controller::balance_control(const float angle_roll, unsigned long sys_time)
{
    // angle_roll: The angle relative to upright, unit: degree
    // *vel_out: The angular velocity of the reaction wheel, unit: rev/sec
    // sys_time: The system time since power up, unit: microsecond

    float dt = (sys_time - last_time) / 1e6f;

    if (dt > 0.0001) {
        // Adjust the offset (i.e., learned setpoint)
        angle_offset += Ki_bias * angle_roll * dt;

        // Corrected angle
        float error = angle_roll - angle_offset;
        float d_error = (error - (last_angle - angle_offset)) / dt;

        // PD Control
        vel_out = Kp * error + Kd * d_error;
        Serial.println(vel_out);

        // Update stored values
        last_angle = angle_roll;
        last_time = sys_time;
    }
    return vel_out;
}