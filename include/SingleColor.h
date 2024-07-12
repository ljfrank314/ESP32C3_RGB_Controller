#ifndef SINGLECOLOR_U
#define SINGLECOLOR_U

#include <vector>
#include "Color.h"
#include "Step.h"
#include "SetColor.h"
#include <Arduino.h>

Color handleSingleColor(int& period, int& colorTime, unsigned long& currentTime, unsigned long& startTime, Color& currentColor, std::vector<Color>& sequentialColorList);

#endif //SINGLECOLOR_U