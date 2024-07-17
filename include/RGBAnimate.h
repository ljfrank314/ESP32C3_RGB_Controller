#ifndef RGBANIMATE_U
#define RGBANIMATE_U

#include <Arduino.h>
#include "RGBQueue.h"
#include "RGBConfig.h"

class RGBAnimate
{
public:
    RGBAnimate(int& period, int& time, RGBQueue& queue, RGBConfig& config);
};

#endif