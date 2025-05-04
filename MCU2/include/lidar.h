
#ifndef __LIDAR_H__
#define __LIDAR_H__

#include <Arduino.h>
#include "parameters.h"

const int N = 20;

class Lidar{
public:
    int distance[N]{};
    int min_distance = DESIRED_DISTANCE;
    int min_idx = 0;
    void initialize();
    void update();
    int counter = 0;
private:
    int pos = 10, dir = -1;
};

#endif
