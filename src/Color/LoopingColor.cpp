#include "LoopingColor.h"

void handleLoopingColor(int& i, float &period, int &colorTime, unsigned long &currentTime, unsigned long &startTime, Color &localColor, std::vector<Color> &loopingColorList)
{
    Color color(0,0,0);
    
    if (colorTime < loopingColorList.at(i).riseTime)
    {
        int deltaRed = loopingColorList.at(i).red - localColor.red;
        int deltaGreen = loopingColorList.at(i).green - localColor.green;
        int deltaBlue = loopingColorList.at(i).blue - localColor.blue;

        float weight = robjohn(colorTime, loopingColorList.at(i).riseTime, loopingColorList.at(i).alpha);

        color.red = static_cast<int>(localColor.red + (deltaRed * weight));
        color.green = static_cast<int>(localColor.green + (deltaGreen * weight));
        color.blue = static_cast<int>(localColor.blue + (deltaBlue * weight));

        colorTime += period;
        localColor = color;
    }
    else
    {
        localColor = loopingColorList.at(i);
        if (i < loopingColorList.size()) i++;
        else i = 0;
        colorTime = 0;
    }
}