#include <Arduino.h>
#include "lidar.h"
#ifndef __BIKE_H__
#define __BIKE_H__

class Bike{
    public:
        int angle;
        int speed;
        Bike() : angle(0), speed(0){};
        void initialize();
        void update(Lidar);
    private:
    //     void turn(Target);
        void move(Lidar);
        void fit();
};

#endif
