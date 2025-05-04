
#include <Arduino.h>
#include <Servo.h>
#include "lidar.h"
#include "parameters.h"

Servo Servo1;

void Lidar::initialize(){
    Servo1.attach(5);
    Servo1.write(90);
    for(int i = 0; i < N; ++i)
        distance[i] = DESIRED_DISTANCE;
}

/*
void Lidar::update(){
    pos += dir;
    if(pos == 0) dir *= -1;
    else if(pos == N - 1) dir *= -1;
    Servo1.write(map(pos, 0, N-1, LIDAR_ANG_MIN, LIDAR_ANG_MAX));
    distance[pos] = map(analogRead(A0), 0, 1023, 5500, 0);

    min_idx = 0;
    min_distance = 1e4;
    for(int i = 0; i < N; ++i)
    {
        if(distance[i] < distance[min_idx])
        {
            min_distance = distance[i];
            min_idx = i;
        }
    }
}
*/

void Lidar::update(){
    int newPos = pos + dir;
    if(newPos < 0 || newPos >= N) dir *= -1;
    pos += dir;
    // int angle = map(pos, 0, N-1, LIDAR_ANG_MIN, LIDAR_ANG_MAX);
    // Servo1.write(angle); // maybe cache last angle to avoid repeat?

    distance[pos] = map(analogRead(A0), 0, 1023, 5500, 0);
}