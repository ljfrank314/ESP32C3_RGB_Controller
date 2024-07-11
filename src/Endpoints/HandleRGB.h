#ifndef HANDLERGB_H
#define HANDLERGB_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <vector>
#include "Color.h"

void handleRGB(std::vector<Color>& sequentionalColorList, std::vector<Color>& loopingColorList, WebServer& server);

#endif // HANDLERGB_H