#include "LoopingColor.h"

Color handleLoopingColor(int& i, int& period, int& colorTime, unsigned long& currentTime, unsigned long& startTime, Color& currentColor, std::vector<Color>& loopingColorList)
{
    Color color(0,0,0);
    if (colorTime < abs(loopingColorList.at(i).riseTime))
    {
        int deltaRed = loopingColorList.at(i).red - currentColor.red;
        int deltaGreen = loopingColorList.at(i).green - currentColor.green;
        int deltaBlue = loopingColorList.at(i).blue - currentColor.blue;

        float weight = robjohn(colorTime, loopingColorList.at(i).riseTime, loopingColorList.at(i).alpha);

        color.red = static_cast<int>(currentColor.red + (deltaRed * weight));
        color.green = static_cast<int>(currentColor.green + (deltaGreen * weight));
        color.blue = static_cast<int>(currentColor.blue + (deltaBlue * weight));
        color.riseTime = loopingColorList.at(i).riseTime;
        color.alpha = loopingColorList.at(i).alpha;

        colorTime += period;
    }
    else
    {
        if (loopingColorList.at(i).alpha > 0) 
        {
            color = loopingColorList.at(i);
        }
        currentColor = color;
        if (i < (loopingColorList.size()-1)) i++;
        else i = 0;
        colorTime = 0;
    }
    return color;
}