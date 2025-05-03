#include <Arduino.h>
#include <Servo.h>
#include "target.h"
#ifndef __GIMBAL_H__
#define __GIMBAL_H__

class Gimbal
{
    public:
        int angle = 90;
        void initialize();
        void update(Target);
    private:
        void turn(Target);
};

#endif