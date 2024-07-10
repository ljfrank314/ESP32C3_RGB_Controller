#include "Color.h"

Color::Color(int r, int g, int b, float t) : red(r), green(g), blue(b), riseTime(t) {}
Color::Color(int r, int g, int b) : red(r), green(g), blue(b), riseTime(1000.f) {}

bool Color::operator==(const Color& other) const
{
    return (red == other.red && blue == other.blue && green == other.green);
}

bool Color::operator!=(const Color &other) const
{
    return !(red == other.red && blue == other.blue && green == other.green);
}
