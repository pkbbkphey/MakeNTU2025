#include <Arduino.h>
#include "target.h"
#ifndef __BIKE_H__
#define __BIKE_H__

class Bike{
    public:
        int angle;
        int speed;
        Bike() : angle(0), speed(0){};
        void initialize();
        void upadate(Target);
    private:
        void turn(Target);
        void move(Target);
        void fit();
};

#endif
