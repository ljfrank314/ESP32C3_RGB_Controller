#include "SingleColor.h"


Color handleSingleColor(int& period, int& colorTime, unsigned long& currentTime, unsigned long& startTime, Color& currentColor, std::vector<Color>& sequentialColorList)
{
    Color color(0,0,0);
    if (colorTime < abs(sequentialColorList.back().riseTime))
    {
        int deltaRed = sequentialColorList.back().red - currentColor.red;
        int deltaGreen = sequentialColorList.back().green - currentColor.green;
        int deltaBlue = sequentialColorList.back().blue - currentColor.blue;

        float weight = robjohn(colorTime, sequentialColorList.back().riseTime, sequentialColorList.back().alpha);

        color.red = static_cast<int>(currentColor.red + (deltaRed * weight));
        color.green = static_cast<int>(currentColor.green + (deltaGreen * weight));
        color.blue = static_cast<int>(currentColor.blue + (deltaBlue * weight));
        color.riseTime = sequentialColorList.back().riseTime;
        color.alpha = sequentialColorList.back().alpha;

        colorTime += period;
    }
    else
    {
        //conditional that allows negative alpha values to produce falling sawtooth animations without flashing
        if (sequentialColorList.back().alpha > 0)
        {
            color = sequentialColorList.back();
        }
        currentColor = color;
        sequentialColorList.pop_back();
        colorTime = 0;
    }

    return color;
}
