#include <Arduino.h>
#include "target.h"
#ifndef __GIMBAL_H__
#define __GIMBAL_H__

class Gimbal
{
    public:
        int angle;
        void turn(Target);
};

#endif