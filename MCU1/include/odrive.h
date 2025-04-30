
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

// Arduino without spare serial ports (such as Arduino UNO) have to use software serial.
// Note that this is implemented poorly and can lead to wrong data sent or read.
// pin 8: RX - connect to ODrive TX
// pin 9: TX - connect to ODrive RX
SoftwareSerial odrive_serial(8, 9);

ODriveArduino odrive(odrive_serial);

class ODrive
{
    public:
        ODrive();
        ~ODrive();
        void initialize();
        void writeVel(float velocity);
    private:
};

#endif