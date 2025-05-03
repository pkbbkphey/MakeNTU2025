#include "target.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial espSerial(8, 9);

void Target::initialize()
{
    espSerial.begin(115200); // ESP32-CAM default baud rate

    //Serial.println("Arduino Nano is ready to communicate with ESP32-CAM");
}

void Target::communicate()
{
    // From ESP32-CAM to PC
    if (espSerial.available())
    {
        char c = espSerial.read();
        Serial.write(c);
    }
}

