
#ifndef __BALANCE_CONTROLLER_H__
#define __BALANCE_CONTROLLER_H__

// class balance_controller{
//     public:
//         float balance_control(const float angle_roll, unsigned long sys_time);

//     private:
//         const float Kp = 0.15;
//         const float Kd = 0.005;
//         const float Ki_bias = 0.001;    // Slow integral gain for equilibrium shift

//         float last_angle = 0.0;
//         unsigned long last_time = 0;
//         float angle_offset = 0.0;       // Adaptive setpoint (learned offset)

//         float vel_out = 0;
// };

// class balance_controller {
//     public:
//         float balance_control(const float angle_roll, unsigned long sys_time);
    
//     private:
//         const float Kp = 6;        // Proportional gain for angle
//         const float Kd = 1;       // Derivative gain for angle velocity
//         // const float Ki_bias = 0.1;  // Learning rate for upright offset
//         const float friction = 0.05;  // Damping/friction to reduce wheel speed near upright
    
//         float last_angle = 0.0;
//         unsigned long last_time = 0;
//         float angle_offset = 0.0;
    
//         float vel_out = 0;            // Current wheel speed (rev/sec)
// };

class balance_controller {
    public:
        float balance_control(float angle_roll_deg, float angle_rate_deg_s, float wheel_speed, unsigned long sys_time);
    
    private:
        const float k1 = 10.0;
        const float k2 = 2.5;
        const float k3 = 1.0;
    
        const float deg2rad = 3.14159 / 180.0;

        unsigned long last_time = 0;
    
        float vel_out = 0;
};
    

#endif