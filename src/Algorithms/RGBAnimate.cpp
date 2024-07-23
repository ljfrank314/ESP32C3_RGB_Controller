#include "RGBAnimate.h"

RGBAnimate::RGBAnimate(int &period, unsigned long &time, RGBQueue& queue, RGBConfig& config)
{
    int currentFrameRed = queue.animation.frames[queue.iterator].red;
    int currentFrameGreen = queue.animation.frames[queue.iterator].green;
    int currentFrameBlue = queue.animation.frames[queue.iterator].blue;
    int currentFrameRiseTime = queue.animation.frames[queue.iterator].riseTime;
    float currentFrameAlpha = queue.animation.frames[queue.iterator].alpha;

    if (time <= currentFrameRiseTime)
    {
        if (currentFrameRiseTime - time < period) time = currentFrameRiseTime;

        int deltaRed = queue.animationDeltas[2][0] - queue.animationDeltas[0][0];
        int deltaGreen = queue.animationDeltas[2][1] - queue.animationDeltas[0][1];
        int deltaBlue = queue.animationDeltas[2][2] - queue.animationDeltas[0][2];

        float weight = robjohn(time, currentFrameRiseTime, currentFrameAlpha);
        queue.animateRGB(
            queue.animationDeltas[0][0] + (deltaRed * weight),
            queue.animationDeltas[0][1] + (deltaGreen * weight),
            queue.animationDeltas[0][2] + (deltaBlue * weight));

        //if colorTime + period is going to overshoot the risetime, set time to risetime so the full color is reached on the last frame
        time += period;
    }
    else
    {       
        queue.loadArray(true);
    }
    
}
