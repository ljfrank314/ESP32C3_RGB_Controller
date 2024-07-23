#ifndef RGBQUEUE_H
#define RGBQUEUE_H

#include "Color.h"
#include "RGBConfig.h"
#include "Step.h"

class RGBQueue
{
public:
    int animationDeltas[3][3];

    RGBQueue(unsigned long& time);

    Animation animation;

    void addColor(int index, int red, int green, int blue, int riseTime, float alpha, bool looping);

    void loadArray(bool iterate);

    void animateRGB(int red, int green, int blue);

    int iterator;

private:
    unsigned long& time;
};

#endif