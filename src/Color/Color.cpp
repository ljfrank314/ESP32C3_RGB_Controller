#include "Color.h"

bool Animation::Color::operator==(const Color &other) const
{
    return (red == other.red && blue == other.blue && green == other.green);
}

bool Animation::Color::operator!=(const Color &other) const
{
    return !(red == other.red && blue == other.blue && green == other.green);
}

void Animation::setFrame(int iterator, int red, int green, int blue, int riseTime, float alpha, bool looping) 
{
    frames[iterator].red = red;
    frames[iterator].green = green;
    frames[iterator].blue = blue;
    frames[iterator].riseTime = riseTime;
    frames[iterator].alpha = alpha;
    frames[iterator].looping = looping;
}

void Animation::setFrame(int iterator)
{
    frames[iterator].red = 0;
    frames[iterator].green = 0;
    frames[iterator].blue = 0;
    frames[iterator].riseTime = 0;
    frames[iterator].alpha = 0;
    frames[iterator].looping = 0;
}

bool Animation::loopEnd(int iterator)
{
    return (frames[iterator+1].looping);
}
