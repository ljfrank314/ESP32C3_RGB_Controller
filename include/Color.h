#ifndef COLOR_H
#define COLOR_H

class Color
{
public:

    int red;
    int green;
    int blue;
    const int riseTime;
    const float alpha;
    const bool looping;

    Color(int red, int green, int blue, int riseTime, float alpha, bool looping);
    Color(int red, int green, int blue);

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
};

#endif //COLOR_H