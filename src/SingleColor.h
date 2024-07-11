#ifndef SINGLECOLOR_U
#define SINGLECOLOR_U

#include <vector>
#include "Color.h"
#include "Step.h"
#include <Arduino.h>

void handleSingleColor(float& period, int& colorTime, unsigned long& currentTime, unsigned long& startTime, Color& localColor, std::vector<Color>& colorList);

#endif //SINGLECOLOR_U