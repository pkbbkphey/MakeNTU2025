// 龍頭&後輪控制
#include <Arduino.h>

struct CTL{
    int yval=0, ypin = 0; 
    int control() {
        yval = analogRead(ypin); 
        return yval;
    }
};