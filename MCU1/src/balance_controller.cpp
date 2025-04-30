
void balance_control(const float angle_roll, float &vel_out, unsigned long sys_time)
{
    // angle_roll: The angle relative to upright, unit: degree
    // vel_out: The angular velocity of the reaction wheel, unit: rev/sec
    // sys_time: The system time since power up, unit: microsecond
    const float Kp = 1.5;
    const float Kd = 0.05;
    const float Ki_bias = 0.001;  // Slow integral gain for equilibrium shift

    static float last_angle = 0.0;
    static unsigned long last_time = 0;
    static float angle_offset = 0.0; // Adaptive setpoint (learned offset)

    float dt = (sys_time - last_time) / 1e6;

    if (dt > 0.0001) {
        // Adjust the offset (i.e., learned setpoint)
        angle_offset += Ki_bias * angle_roll * dt;

        // Corrected angle
        float error = angle_roll - angle_offset;
        float d_error = (error - (last_angle - angle_offset)) / dt;

        // PD Control
        vel_out = Kp * error + Kd * d_error;

        // Update stored values
        last_angle = angle_roll;
        last_time = sys_time;
    }
}