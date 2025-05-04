#include <Arduino.h>
#include "lidar.h"
#include "bike.h"

Bike bike;
Lidar lidar;

unsigned long lastUpdate = 0;
const unsigned long updateInterval = 100; // ms

void setup()
{
    Serial.begin(115200);
    bike.initialize();
    lidar.initialize();
}

void loop()
{
    unsigned long now = millis();
    if (now - lastUpdate >= updateInterval || now < lastUpdate) {
        lidar.update();
        bike.update(lidar);
        lastUpdate = now;
    }
}
