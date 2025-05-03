#include <gimbal.h>

void Gimbal::turn(Target tar){ // mm
    int disx = tar.x, distance = tar.distance;
    double ang = atan2(distance, disx) * 180 / M_PI;
    ang = 90 - ang;
    angle = angle + (ang - angle) / 2;
    // TODO: lost()
}