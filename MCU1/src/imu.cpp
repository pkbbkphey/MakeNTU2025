
// REFERANCE:
// http://www.brokking.net/imu.html

#include <Wire.h>
#include <EEPROM.h>
#include <Arduino.h>
#include "imu.h"

MPU6050::MPU6050(){
}

MPU6050::~MPU6050(){
}

void MPU6050::initialize()
{
    Wire.begin(); // Start I2C as master
    pinMode(LED_BUILTIN, OUTPUT);

    setup_mpu_6050_registers(); // Setup the registers of the MPU-6050 (500dfs / +/-8g) and start the gyro

    gyro_x_cal = (EEPROM.read(3) << 24) | (EEPROM.read(2) << 16) | (EEPROM.read(1) << 8) | EEPROM.read(0);
    gyro_y_cal = (EEPROM.read(7) << 24) | (EEPROM.read(6) << 16) | (EEPROM.read(5) << 8) | EEPROM.read(4);
    gyro_z_cal = (EEPROM.read(11) << 24) | (EEPROM.read(10) << 16) | (EEPROM.read(9) << 8) | EEPROM.read(8);
}

void MPU6050::calibrate()
{
    digitalWrite(LED_BUILTIN, HIGH);

    delay(1500);

    Serial.println("Calibrating gyro");

    for (int cal_int = 0; cal_int < 2000; cal_int++)
    {
        read_mpu_6050_data(); // Read the raw acc and gyro data from the MPU-6050
        gyro_x_cal += gyro_x; // Add the gyro x-axis offset to the gyro_x_cal variable
        gyro_y_cal += gyro_y;
        gyro_z_cal += gyro_z;
        delay(3); // Delay 3us to simulate the 250Hz program loop
    }
    gyro_x_cal /= 2000; // avarage offset
    gyro_y_cal /= 2000;
    gyro_z_cal /= 2000;

    EEPROM.write(0, gyro_x_cal & 0x000000FF);
    EEPROM.write(1, (gyro_x_cal >> 8) & 0x000000FF);
    EEPROM.write(2, (gyro_x_cal >> 16) & 0x000000FF);
    EEPROM.write(3, (gyro_x_cal >> 24) & 0x000000FF);

    EEPROM.write(4, gyro_y_cal & 0x000000FF);
    EEPROM.write(5, (gyro_y_cal >> 8) & 0x000000FF);
    EEPROM.write(6, (gyro_y_cal >> 16) & 0x000000FF);
    EEPROM.write(7, (gyro_y_cal >> 24) & 0x000000FF);

    EEPROM.write(8, gyro_z_cal & 0x000000FF);
    EEPROM.write(9, (gyro_z_cal >> 8) & 0x000000FF);
    EEPROM.write(10, (gyro_z_cal >> 16) & 0x000000FF);
    EEPROM.write(11, (gyro_z_cal >> 24) & 0x000000FF);

    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Calibration finished");
}

void MPU6050::update()
{
    read_mpu_6050_data();

    gyro_x -= gyro_x_cal; // Subtract the avarage offset value from the raw gyro_x value
    gyro_y -= gyro_y_cal;
    gyro_z -= gyro_z_cal;

    // Gyro angle calculations
    // 0.0000611 = 1 / (250Hz / 65.5)
    angle_pitch += gyro_x * 0.0000611; // Calculate the traveled pitch angle and add this to the angle_pitch variable
    angle_roll += gyro_y * 0.0000611;  // Calculate the traveled roll angle and add this to the angle_roll variable

    // 0.000001066 = 0.0000611 * (3.142(PI) / 180degr) The Arduino sin function is in radians
    angle_pitch += angle_roll * sin(gyro_z * 0.000001066); // If the IMU has yawed transfer the roll angle to the pitch angel
    angle_roll -= angle_pitch * sin(gyro_z * 0.000001066); // If the IMU has yawed transfer the pitch angle to the roll angel

    // Accelerometer angle calculations
    acc_total_vector = sqrt((acc_x * acc_x) + (acc_y * acc_y) + (acc_z * acc_z)); // Calculate the total accelerometer vector
    // 57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
    angle_pitch_acc = asin((float)acc_y / acc_total_vector) * 57.296; // Calculate the pitch angle
    angle_roll_acc = asin((float)acc_x / acc_total_vector) * -57.296; // Calculate the roll angle

    // Place the MPU-6050 spirit level and note the values in the following two lines for calibration
    angle_pitch_acc -= 0.0; // Accelerometer calibration value for pitch
    angle_roll_acc -= 0.0;  // Accelerometer calibration value for roll

    if (set_gyro_angles)
    {                                                                  // If the IMU is already started
        angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004; // Correct the drift of the gyro pitch angle with the accelerometer pitch angle
        angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;    // Correct the drift of the gyro roll angle with the accelerometer roll angle
    }
    else
    {                                  // At first start
        angle_pitch = angle_pitch_acc; // Set the gyro pitch angle equal to the accelerometer pitch angle
        angle_roll = angle_roll_acc;   // Set the gyro roll angle equal to the accelerometer roll angle
        set_gyro_angles = true;        // Set the IMU started flag
    }

    // To dampen the pitch and roll angles a complementary filter is used
    angle_pitch_output = angle_pitch_output * 0.9 + angle_pitch * 0.1; // Take 90% of the output pitch value and add 10% of the raw pitch value
    angle_roll_output = angle_roll_output * 0.9 + angle_roll * 0.1;    // Take 90% of the output roll value and add 10% of the raw roll value

    angle_pitch_buffer = angle_pitch_output * 10 - 6;
    angle_roll_buffer = angle_roll_output * 10 + 53; //(6, -53)
    // Serial.print(angle_pitch_buffer);
    // Serial.print("     ");
    // Serial.println(angle_roll_buffer);

    // delay(4);
    // while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
    // loop_timer = micros();                                               //Reset the loop timer
}

void MPU6050::read_mpu_6050_data()
{                                 // Subroutine for reading the raw gyro and accelerometer data
    Wire.beginTransmission(0x68); // Start communicating with the MPU-6050
    Wire.write(0x3B);             // Send the requested starting register
    Wire.endTransmission();       // End the transmission
    Wire.requestFrom(0x68, 14);   // Request 14 bytes from the MPU-6050
    while (Wire.available() < 14)
        ;                                         // Wait until all the bytes are received
    acc_x = Wire.read() << 8 | Wire.read();       // Add the low and high byte to the acc_x variable
    acc_y = Wire.read() << 8 | Wire.read();       // Add the low and high byte to the acc_y variable
    acc_z = Wire.read() << 8 | Wire.read();       // Add the low and high byte to the acc_z variable
    temperature = Wire.read() << 8 | Wire.read(); // Add the low and high byte to the temperature variable
    gyro_x = Wire.read() << 8 | Wire.read();      // Add the low and high byte to the gyro_x variable
    gyro_y = Wire.read() << 8 | Wire.read();      // Add the low and high byte to the gyro_y variable
    gyro_z = Wire.read() << 8 | Wire.read();      // Add the low and high byte to the gyro_z variable
}

void MPU6050::setup_mpu_6050_registers()
{
    // Activate the MPU-6050
    Wire.beginTransmission(0x68); // Start communicating with the MPU-6050
    Wire.write(0x6B);             // Send the requested starting register
    Wire.write(0x00);             // Set the requested starting register
    Wire.endTransmission();       // End the transmission
    // Configure the accelerometer (+/-8g)
    Wire.beginTransmission(0x68); // Start communicating with the MPU-6050
    Wire.write(0x1C);             // Send the requested starting register
    Wire.write(0x10);             // Set the requested starting register
    Wire.endTransmission();       // End the transmission
    // Configure the gyro (500dps full scale)
    Wire.beginTransmission(0x68); // Start communicating with the MPU-6050
    Wire.write(0x1B);             // Send the requested starting register
    Wire.write(0x08);             // Set the requested starting register
    Wire.endTransmission();       // End the transmission
}
