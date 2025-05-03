#include <Arduino.h>
#ifndef __TARGET_H__
#define __TARGET_H__

class Target
{
    public:
        int x, y, size;
        int distance;
        void initialize();
        void communicate();
    private:
        String input_string;
        void parse(String, int);
};

#endif