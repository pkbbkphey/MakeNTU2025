
#include "ODriveArduino.h"
#include <SoftwareSerial.h>

#ifndef __ODRIVE_H__
#define __ODRIVE_H__

// Printing with stream operator helper functions
template <class T>
inline Print &operator<<(Print &obj, T arg)
{
    obj.print(arg);
    return obj;
}
template <>
inline Print &operator<<(Print &obj, float arg)
{
    obj.print(arg, 4);
    return obj;
}

class ODrive
{
    public:
        ODrive();
        ~ODrive();
        void initialize();
        void writeVel(float velocity);
        float readVel();
    private:
};

void test();

#endif