#ifndef COLOR_H
#define COLOR_H

struct Animation
{
    const int totalFrames = 99;
    struct Color
    {
        int red;
        int green;
        int blue;
        int riseTime;
        float alpha;
        bool looping;

        bool operator==(const Color& other) const;
        bool operator!=(const Color& other) const;

        Color() : red(0), green(0), blue(0), riseTime(0), alpha(0), looping(0) {};
    } frames[100];

    Animation() {}

    void setFrame(int iterator, int red, int green, int blue, int riseTime, float alpha, bool looping);
    void setFrame(int iterator);
    bool loopEnd(int iterator);
};


#endif //COLOR_H