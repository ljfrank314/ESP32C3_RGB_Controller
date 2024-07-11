#include "Color.h"

Color::Color(int r, int g, int b, int t, float a) : red(r), green(g), blue(b), riseTime(t), alpha(a) {}
Color::Color(int r, int g, int b) : red(r), green(g), blue(b), riseTime(1000.f), alpha(1.f) {}

bool Color::operator==(const Color& other) const
{
    return (red == other.red && blue == other.blue && green == other.green);
}

bool Color::operator!=(const Color &other) const
{
    return !(red == other.red && blue == other.blue && green == other.green);
}
