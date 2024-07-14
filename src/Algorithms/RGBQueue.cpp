#include "RGBQueue.h"

RGBQueue::RGBQueue()
: lunchLine(), animationDeltas(), iterator(0), iteratorMax(0)
{
    setZeros();
}

void RGBQueue::addColor(Color color)
{
    if (!color.looping)
    {
        lunchLine.clear();
    }
    lunchLine.push
}

void RGBQueue::setRGB(Color color)
{
    animationDeltas[1][0] = color.red;
    animationDeltas[1][1] = color.green;
    animationDeltas[1][2] = color.blue;
}

int RGBQueue::loadArray()
{
    if (!lunchLine.empty())
    {
        animationDeltas[0][0] = animationDeltas[1][0];
        animationDeltas[0][1] = animationDeltas[1][1];
        animationDeltas[0][2] = animationDeltas[1][2];

        if (!lunchLine.front().looping)
        {
            animationDeltas[2][0] = lunchLine.front().red;
            animationDeltas[2][1] = lunchLine.front().green;
            animationDeltas[2][2] = lunchLine.front().blue;
            lunchLine.pop_front();

            return 0;
        }

        animationDeltas[2][0] = lunchLine.at(iterator).red;
        animationDeltas[2][1] = lunchLine.at(iterator).green;
        animationDeltas[2][2] = lunchLine.at(iterator).blue;

        incrementIterator(1);
    } 
}

int RGBQueue::getRed()
{
    return 0;
}

int RGBQueue::getGreen()
{
    return 0;
}

int RGBQueue::getBlue()
{
    return 0;
}

void RGBQueue::reset()
{
    setZeros();
    lunchLine.clear();
    lunchLine.shrink_to_fit();
}

void RGBQueue::incrementIterator(int delta)
{
    if (iterator >= iteratorMax) //switch might be faster here but i never learned em
    {
        iterator = 0;
    }
    else
    {
        iterator = iterator + delta;
    }
}

void RGBQueue::setIteratorMax()
{
    iteratorMax = lunchLine.size() - 1;
}

void RGBQueue::setZeros()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; i < 3; i++)
        {
            animationDeltas[i][j] = 0;
        }
    }
}
