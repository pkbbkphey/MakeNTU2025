
#include "odrive.h"
#include "ODriveArduino.h"
#include <SoftwareSerial.h>

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