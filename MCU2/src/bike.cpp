// 龍頭&後輪控制
#include <Arduino.h>
#include <Servo.h>
#include <AccelStepper.h>
#include "parameters.h"
#include "lidar.h"
#include "bike.h"
#include "control.cpp"

#define Kp 0.3

const int MAX_ANGLE = 90, MIN_ANGLE = -90;
const int MAX_SPEED = 100, MIN_SPEED = 0;
const int RESERVED_TIME = 2;// time for the bike to collide with static tracing object
// const int DESIRED_DISTANCE = 2500; // in mm
// const int GATE_DISTANCE_VALUE = 9e18;

Servo Esc;
AccelStepper STEPPER1(1, 11, 10);
CTL ctl;

void Bike::initialize()
{
    Esc.attach(6);
    
    STEPPER1.setEnablePin(12);
    STEPPER1.setMaxSpeed(1000);
    delay(1000);
    STEPPER1.enableOutputs();
    delay(500);
    STEPPER1.setCurrentPosition(0);
}

void Bike::update(Lidar lidar)
{
    // turn(tar);
    move(lidar);
    Esc.write(map(speed, 0, 100, 90, 100));
    int new_angle = map(ctl.control(), 0, 1023, 0, 100);
    STEPPER1.moveTo(new_angle);
    STEPPER1.run();
}

void Bike::fit(){
    angle = max(MIN_ANGLE, min(angle, MAX_ANGLE));
    speed = max(MIN_SPEED, min(speed, MAX_SPEED));
}

// void Bike::turn(Target tar){ // mm
//     int disx = tar.x, distance = tar.distance;
//     double ang = atan2(distance, disx) * 180 / M_PI;
//     ang = 90 - ang;
//     angle = angle + (ang - angle) / 2;
//     fit();
// }


void Bike::move(Lidar lidar){

    lidar.min_idx = 0;
    lidar.min_distance = 1e4;

    for(int i = 0; i < N; ++i)
    {
        if(lidar.distance[i] < lidar.distance[lidar.min_idx])
        {
            lidar.min_distance = lidar.distance[i];
            lidar.min_idx = i;
        }
    }
    double new_speed = (lidar.min_distance - DESIRED_DISTANCE) * Kp;
    speed = new_speed;
    fit();
}

