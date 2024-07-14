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

    void loadArray();

    void setRGB(Color color);

    void reset();

private:
    int iterator;
    int iteratorMax;

    int maxSize;
    
    /// @brief Deque of the queued colors
    std::deque<Color> lunchLine;

    void incrementIterator(int delta);

    void setIteratorMax();

    void setZeros();
};

#endif