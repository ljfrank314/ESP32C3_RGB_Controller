#ifndef RGBANIMATE_U
#define RGBANIMATE_U

#include <Arduino.h>
#include "RGBQueue.h"
#include "RGBConfig.h"

class RGBAnimate
{
public:
    RGBAnimate(int& period, unsigned long& time, RGBQueue& queue, RGBConfig& config);
};

#endif