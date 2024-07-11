#include "SingleColor.h"


void handleSingleColor(float& period, int& colorTime, unsigned long& currentTime, unsigned long& startTime, Color& localColor, std::vector<Color>& colorList)
{
    Color color(0,0,0);
    digitalWrite(D8,HIGH);
    if (colorTime < colorList.back().riseTime)
    {
        int deltaRed = colorList.back().red - localColor.red;
        int deltaGreen = colorList.back().green - localColor.green;
        int deltaBlue = colorList.back().blue - localColor.blue;

        float weight = robjohn(colorTime, colorList.back().riseTime, colorList.back().alpha);

        color.red = static_cast<int>(localColor.red + (deltaRed * weight));
        color.green = static_cast<int>(localColor.green + (deltaGreen * weight));
        color.blue = static_cast<int>(localColor.blue + (deltaBlue * weight));
        Serial.printf("    color rgb: %i %i %i \n", color.red, color.green, color.blue);
        Serial.printf("     riseTime: %f \n", colorList.back().riseTime);
        Serial.printf("       Weight: %f \n",weight);
        colorTime += period;
        localColor = color;
    }
    else
    {
        localColor = colorList.back();
        colorList.pop_back();
        colorTime = 0;
        digitalWrite(D9,LOW);
        digitalWrite(D8,LOW);
        digitalWrite(D7,LOW);
    }
}
