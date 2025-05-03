#include <Arduino.h>
#ifndef __BIKE_H__
#define __BIKE_H__

class bike{
public:
    int angle;
    int speed;
    bike() : angle(0), speed(0){};
    void turn();
    void move();
};

#endif
