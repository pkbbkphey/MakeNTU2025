
#ifndef __IMU_H__
#define __IMU_H__

class MPU6050
{
    public:
        MPU6050();
        ~MPU6050();
        void initialize();
        void update();
        int gyro_x, gyro_y, gyro_z;
        long acc_x, acc_y, acc_z, acc_total_vector;
        int temperature;
        long gyro_x_cal, gyro_y_cal, gyro_z_cal;
        float angle_pitch, angle_roll;
        int angle_pitch_buffer, angle_roll_buffer;
        bool set_gyro_angles;
        float angle_roll_acc, angle_pitch_acc;
        float angle_pitch_output, angle_roll_output;
    private:
        void read_mpu_6050_data();
        void setup_mpu_6050_registers();
};

#endif