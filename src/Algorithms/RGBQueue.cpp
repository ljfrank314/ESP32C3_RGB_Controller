#include "RGBQueue.h"

RGBQueue::RGBQueue() : iterator(0)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; i < 3; i++)
        {
            animationDeltas[i][j] = 0;
        }
    }
}

void RGBQueue::addColor(int index, int red, int green, int blue, int riseTime, float alpha, bool looping)
{
    if (index < animation.totalFrames) //idk if this is faster than lunchLine.size();
    {    
        if (!looping)
        {
            animation.setFrame(index + 1);
        }
        animation.setFrame(index, red, green, blue, riseTime, alpha, false);

        iterator = 0;
    }
}

void RGBQueue::animateRGB(int red, int green, int blue)
{
    animationDeltas[1][0] = red;
    animationDeltas[1][1] = green;
    animationDeltas[1][2] = blue;
}

void RGBQueue::loadArray()
{
    animationDeltas[0][0] = animationDeltas[1][0];
    animationDeltas[0][1] = animationDeltas[1][1];
    animationDeltas[0][2] = animationDeltas[1][2];

    animationDeltas[2][0] = animation.frames[0].red;
    animationDeltas[2][1] = animation.frames[0].green;
    animationDeltas[2][2] = animation.frames[0].blue;
    if (animation.frames[0].looping && !animation.loopEnd(iterator))
    {
        iterator++;
    }
    else
    {
        iterator = 0;
    }
}