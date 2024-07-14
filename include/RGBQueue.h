#ifndef RGBQUEUE_H
#define RGBQUEUE_H

#include "Color.h"
#include <deque>
#include <inttypes.h>

class RGBQueue
{
public:

    int animationDeltas[3][3];
    RGBQueue();

    void addColor(Color color);

    int loadArray();

    void setRGB(Color color);
    int getRed();
    int getGreen();
    int getBlue();

    void reset();

private:
    int iterator;
    int iteratorMax;
    
    /// @brief Deque of the queued colors
    std::deque<Color> lunchLine;

    void incrementIterator(int delta);

    void setIteratorMax();

    void setZeros();
};

#endif