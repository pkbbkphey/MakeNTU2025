// 龍頭&後輪控制
#include <Arduino.h>
#include <Servo.h>
#include <AccelStepper.h>
#include "bike.h"
#include "target.h"
#include "gimbal.h"

#define Kp 0.3

const int MAX_ANGLE = 90, MIN_ANGLE = -90;
const int MAX_SPEED = 100, MIN_SPEED = 0;
const int RESERVED_TIME = 2;// time for the bike to collide with static tracing object
const int DESIRED_DISTANCE = 2500; // in mm
const int GATE_DISTANCE_VALUE = 9e18;

Servo Esc;
AccelStepper STEPPER1(1, 11, 10);

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

void Bike::upadate(Target tar)
{
    turn(tar);
    move(tar);
    Esc.write(map(speed, 0, 100, 90, 100));
    STEPPER1.moveTo(angle);
    STEPPER1.run();
}

void Bike::fit(){
    angle = max(MIN_ANGLE, min(angle, MAX_ANGLE));
    speed = max(MIN_SPEED, min(speed, MAX_SPEED));
}

void Bike::turn(Target tar){ // mm
    int disx = tar.x, distance = tar.distance;
    double ang = atan2(distance, disx) * 180 / M_PI;
    ang = 90 - ang;
    angle = angle + (ang - angle) / 2;
    fit();
}


void Bike::move(Target tar){
    int disx = tar.x, distance = tar.distance;
    if(distance > GATE_DISTANCE_VALUE){
        // lost(); // TODO
    }
    double new_speed = (distance - DESIRED_DISTANCE) * Kp;
    speed = new_speed;
    fit();
}

