#ifndef HANDLERGB_H
#define HANDLERGB_H

#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <vector>
#include "Color.h"

void handleRGB(std::vector<Color>& colorList, WebServer& server);

#endif // HANDLERGB_H