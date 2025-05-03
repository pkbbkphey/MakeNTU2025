#include <Arduino.h>
#include "target.h"
#include "gimbal.h"
#include "bike.h"
#define int long long
#define PIN_ServoPWM
#define PIN_EscPWM
// #define PIN_Tof    // Tof: I2C
// #define PIN_Esp32  // Esp32: UART

const int INF = 9e18;
Bike bike;
Gimbal gimbal;
Target target;

void setup()
{
    Serial.begin(115200);
    target.initialize();
    gimbal.initialize();
    bike.initialize();
}

void loop()
{
    target.communicate();
    // gimbal.update(target);
    // bike.upadate(target);
}
