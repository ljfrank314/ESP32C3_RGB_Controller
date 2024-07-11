#include "SingleColor.h"


void handleSingleColor(float& period, int& colorTime, unsigned long& currentTime, unsigned long& startTime, Color& localColor, std::vector<Color>& sequentialColorList)
{
    Color color(0,0,0);

    if (colorTime < sequentialColorList.back().riseTime)
    {
        int deltaRed = sequentialColorList.back().red - localColor.red;
        int deltaGreen = sequentialColorList.back().green - localColor.green;
        int deltaBlue = sequentialColorList.back().blue - localColor.blue;

        float weight = robjohn(colorTime, sequentialColorList.back().riseTime, sequentialColorList.back().alpha);

        color.red = static_cast<int>(localColor.red + (deltaRed * weight));
        color.green = static_cast<int>(localColor.green + (deltaGreen * weight));
        color.blue = static_cast<int>(localColor.blue + (deltaBlue * weight));

        colorTime += period;
        localColor = color;
    }
    else
    {
        localColor = sequentialColorList.back();
        sequentialColorList.pop_back();
        colorTime = 0;
    }
}
