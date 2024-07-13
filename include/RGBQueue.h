#ifndef RGBQUEUE_H
#define RGBQUEUE_H

#include "Color.h"
#include <deque>
#include <inttypes.h>

class RGBQueue
{
public:
    RGBQueue();

    void addColor(Color color);

    void loadArray();

    int getRed();
    int getGreen();
    int getBlue();

    void reset();

private:
    int iterator;
    
    /// @brief Deque of the queued colors
    std::deque<Color> lunchLine;

    /// @brief Subarrays hold RGB values, subarray represents past, present, and future
    int animationDeltas[3][3]= {
        {0,0,0},
        {0,0,0},
        {0,0,0}};
};

#endif