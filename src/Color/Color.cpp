#include "Color.h"

Color::Color(int red, int green, int blue, int riseTime, float alpha, bool looping)
: red(red), green(green), blue(blue), riseTime(riseTime), alpha(alpha), looping(looping){}

Color::Color(int red, int green, int blue)
: red(red), green(green), blue(blue), riseTime(1000), alpha(3), looping(false){}

bool Color::operator==(const Color &other) const
{
    return (red == other.red && blue == other.blue && green == other.green);
}

bool Color::operator!=(const Color &other) const
{
    return !(red == other.red && blue == other.blue && green == other.green);
}
