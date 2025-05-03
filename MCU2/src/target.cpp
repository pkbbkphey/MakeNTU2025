#include "target.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial espSerial(8, 9);

void Target::initialize()
{
    espSerial.begin(115200); // ESP32-CAM default baud rate

    //Serial.println("Arduino Nano is ready to communicate with ESP32-CAM");
}
 // "  GSW (0.984375) [ x: 16, y: 48, width: 32, height: 16 ]"
void Target::parse(String s, int n){
    int x1 = 0, y1 = 0, w1 = 0, h1 = 0;
    int stat = 0;
    for (int i = 0; i < n; i++){
        char c = s[i];
        // Serial.println(c);
        if(c == ':'){
            stat++;
            continue;
        }
        if(c - '0' < 0 || c - '0' > 9)break;
        if(stat == 0){
            x1 = x1 * 10 + (c - '0');
        }else if(stat == 1){
            y1 = y1 * 10 + (c - '0');
        }else if(stat == 2){
            w1 = w1 * 10 + (c - '0');
        }else if(stat == 3){
            h1 = h1 * 10 + (c - '0');
        }
    }
    x = x1 + w1 / 2, y = y1 + h1 / 2;

    Serial.println(x);
}


void Target::communicate()
{
    // From ESP32-CAM to PC
    digitalWrite(LED_BUILTIN, LOW);
    int sz = 0;
    Serial.println("GOESIN");
    while (espSerial.available() > 0)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println(espSerial.read());
        char c = espSerial.read();
        sz++;
        input_string += c;
        Serial.println(c);
        if(c == '\n'){
            Serial.println("hi");
            parse(input_string, sz);
            input_string = "";
            sz = 0;
            break;
        }
    }

    distance = map(analogRead(A0), 0, 1023, 5500, 0);
    // Serial.println(distance);
}

