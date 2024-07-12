#ifndef LOOPINGCOLOR_U
#define LOOPINGCOLOR_U

#include <vector>
#include "Color.h"
#include "Step.h"
#include "SetColor.h"
#include <Arduino.h>

Color handleLoopingColor(int& loopIterator, int& period, int& colorTime, unsigned long& currentTime, unsigned long& startTime, Color& currentColor, std::vector<Color>& loopingColorList);

#endif //LOOPINGCOLOR_U