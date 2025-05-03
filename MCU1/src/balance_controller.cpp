
#include <Arduino.h>
#include "balance_controller.h"

// float balance_controller::balance_control(const float angle_roll, unsigned long sys_time)
// {
//     // angle_roll: The angle relative to upright, unit: degree
//     // *vel_out: The angular velocity of the reaction wheel, unit: rev/sec
//     // sys_time: The system time since power up, unit: microsecond

//     float dt = (sys_time - last_time) / 1e6f;

//     if (dt > 0.0001) {
//         // Adjust the offset (i.e., learned setpoint)
//         angle_offset += Ki_bias * angle_roll * dt;

//         // Corrected angle
//         float error = angle_roll - angle_offset;
//         float d_error = (error - (last_angle - angle_offset)) / dt;

//         // PD Control
//         vel_out = Kp * error + Kd * d_error;
//         // Serial.println(vel_out);

//         // Update stored values
//         last_angle = angle_roll;
//         last_time = sys_time;
//     }
//     return vel_out;
// }

float balance_controller::balance_control(const float angle_roll, unsigned long sys_time)
{
    float torque = 0;
    float dt = (sys_time - last_time) / 1e6f;  // Convert µs to seconds

    if (dt > 0.0001) {
        // Learn the new balance point slowly
        // angle_offset += Ki_bias * angle_roll * dt;

        // Compute error and derivative
        float error = angle_roll - angle_offset;
        float d_error = (angle_roll - last_angle) / dt;

        // PD control gives desired angular acceleration (i.e., torque)
        torque = Kp * error + Kd * d_error;

        // Update wheel velocity from torque, simulate motor response
        vel_out += torque * dt;

        // Simulate friction or motor damping to return to 0 speed
        vel_out *= (1.0 - friction);  // Exponential decay

        // Store values
        last_angle = angle_roll;
        last_time = sys_time;
    }

    return vel_out;
}

// float balance_controller::balance_control(float angle_roll_deg, float angle_rate_deg_s, float wheel_speed, unsigned long sys_time)
// {
//     // Convert to radians
//     float theta = angle_roll_deg * deg2rad;
//     float theta_dot = angle_rate_deg_s * deg2rad;

//     // LQR control law: u = -Kx
//     float torque = - (k1 * theta + k2 * theta_dot + k3 * wheel_speed);

//     // Integrate torque to get new wheel velocity (rev/sec)
//     float dt = (sys_time - last_time) / 1e6f;
//     if (dt > 0.0001) {
//         vel_out += torque * dt;
//         last_time = sys_time;
//     }

//     return vel_out;
// }
