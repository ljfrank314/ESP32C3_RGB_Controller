#include "RGBAnimate.h"

RGBAnimate::RGBAnimate(int &period, int &time, RGBQueue& queue, RGBConfig& config)
{
    int color[] = {0,0,0};

    if (time < queue.animation.frames[queue.iterator].riseTime)
    {
        int deltaRed = queue.animationDeltas[0][0] - queue.animationDeltas[2][0];
        int deltaGreen = queue.animationDeltas[0][1] - queue.animationDeltas[2][1];
        int deltaBlue = queue.animationDeltas[0][2] - queue.animationDeltas[2][2];

        float weight = robjohn(time, queue.animation.frames[queue.iterator].riseTime, queue.animation.frames[queue.iterator].alpha);

        queue.animationDeltas[1][0] = (queue.animationDeltas[1][0] + (deltaRed * weight));
        queue.animationDeltas[1][1] = (queue.animationDeltas[1][1] + (deltaRed * weight));
        queue.animationDeltas[1][2] = (queue.animationDeltas[1][2] + (deltaRed * weight));

        time += period;
    }
    else
    {
        //conditional that allows negative alpha values to produce falling sawtooth animations without flashing
        if (queue.animation.frames[queue.iterator].alpha > 0)
        {
            queue.animationDeltas[1][0] = queue.animation.frames[queue.iterator].red;
            queue.animationDeltas[1][1] = queue.animation.frames[queue.iterator].green;
            queue.animationDeltas[1][2] = queue.animation.frames[queue.iterator].blue;
        }
        queue.loadArray();
        time = 0;
    }
    config.setRGB(queue.animationDeltas[1][0], queue.animationDeltas[1][1], queue.animationDeltas[1][2]);
}
