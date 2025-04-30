
#include "odrive.h"
#include "ODriveArduino.h"
#include <SoftwareSerial.h>

// Arduino without spare serial ports (such as Arduino UNO) have to use software serial.
// Note that this is implemented poorly and can lead to wrong data sent or read.
// pin 8: RX - connect to ODrive TX
// pin 9: TX - connect to ODrive RX
SoftwareSerial odrive_serial(8, 9);

ODriveArduino odrive(odrive_serial);

ODrive::ODrive()
{

}
ODrive::~ODrive()
{

}

void ODrive::initialize()
{
    // ODrive uses 115200 baud
    odrive_serial.begin(115200);

    for (int axis = 0; axis < 2; ++axis)
    {
        odrive_serial << "w axis" << axis << ".controller.config.vel_limit " << 10.0F << '\n';
        odrive_serial << "w axis" << axis << ".motor.config.current_lim " << 11.0F << '\n';
        // This ends up writing something like "w axis0.motor.config.current_lim 10.0\n"
    }
}

void ODrive::writeVel(float velocity)
{
    // odrive_serial << "v 0 1\n";
    odrive_serial << "v 0 " << String(velocity) << "\n";
}