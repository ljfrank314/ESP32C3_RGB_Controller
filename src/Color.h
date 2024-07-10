#ifndef COLOR_H
#define COLOR_H

class Color
{
public:

    int red;
    int green;
    int blue;
    float riseTime;

    Color(int r, int g, int b, float t);
    Color(int r, int g, int b);

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
};

#endif //COLOR_H