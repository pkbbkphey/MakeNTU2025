#include <bike.h>
#include <target.h>

const int MAX_ANGLE = 90, MIN_ANGLE = -90;
const int MAX_SPEED = 100, MIN_SPEED = 0;
const int RESERVED_TIME = 2;// time for the bike to collide with static tracing object

void bike::fit(){
    angle = max(MIN_ANGLE, min(angle, MAX_ANGLE));
    speed = max(MIN_SPEED, min(speed, MAX_SPEED));
}

void bike::turn(Target tar){ // mm
    int disx = tar.x, distance = tar.distance;
    double ang = atan2(distance, disx) * 180 / M_PI;
    ang = 90 - ang;
    angle = angle + (ang - angle) / 2;
    fit();
}


void bike::move(Target tar){
    int disx = tar.x, distance = tar.distance;
    double new_speed = distance / RESERVED_TIME;
    speed = new_speed;
    fit();
}