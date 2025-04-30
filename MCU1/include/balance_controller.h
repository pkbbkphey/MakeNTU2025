
#ifndef __BALANCE_CONTROLLER_H__
#define __BALANCE_CONTROLLER_H__

class balance_controller{
    public:
        float balance_control(const float angle_roll, unsigned long sys_time);

    private:
        const float Kp = 0.15;
        const float Kd = 0.005;
        const float Ki_bias = 0.001;    // Slow integral gain for equilibrium shift

        float last_angle = 0.0;
        unsigned long last_time = 0;
        float angle_offset = 0.0;       // Adaptive setpoint (learned offset)

        float vel_out = 0;
};

#endif