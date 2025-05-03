#include <gimbal.h>
#include <Servo.h>

Servo Servo1;

void Gimbal::initialize()
{
    Servo1.attach(7);
}

void Gimbal::update(Target tar)
{
    turn(tar);
    Servo1.write(angle + 90);
}

void Gimbal::turn(Target tar){ // mm
    int disx = tar.x, distance = tar.distance;
    // double ang = atan2(distance, disx) * 180 / M_PI;
    double ang = (disx-45) / 90 * 65;
    // ang = 90 - ang;
    // angle = angle + (ang - angle) / 2;
    angle = -ang;
    // TODO: lost()
}