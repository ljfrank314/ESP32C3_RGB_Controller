#ifndef LOOPINGCOLOR_U
#define LOOPINGCOLOR_U

#include <vector>
#include "Color.h"
#include "Step.h"
#include <Arduino.h>

void handleLoopingColor(int& loopIterator, float& period, int& colorTime, unsigned long& currentTime, unsigned long& startTime, Color& localColor, std::vector<Color>& loopingColorList);

#endif //LOOPINGCOLOR_U