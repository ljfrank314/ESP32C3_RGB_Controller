#include <RGBConfig.h>
#include <cmath>
#include <Arduino.h>

RGBConfig::RGBConfig(uint8_t redChannel, uint8_t greenChannel, uint8_t blueChannel, uint32_t frequency)
: redChannel(redChannel), greenChannel(greenChannel), blueChannel(blueChannel), frequency(frequency), resolution(resolution)
{
    ledcSetup(redChannel, frequency, resolution);
    ledcSetup(greenChannel, frequency, resolution);
    ledcSetup(blueChannel, frequency, resolution);
}

bool RGBConfig::setRGB(uint32_t redDuty, uint32_t greenDuty, uint32_t blueDuty)
{
    int maxPWM = static_cast<int>(pow(resolution, 2)-1);
    if (redDuty >= maxPWM && greenDuty >= maxPWM && blueDuty >= maxPWM)
    {
        ledcWrite(redChannel, redDuty);
        ledcWrite(greenChannel, greenDuty);
        ledcWrite(blueChannel, blueDuty);
        return true;
    }
    return false;
}

void RGBConfig::attachRedPin(uint8_t pin)
{
    ledcAttachPin(pin,redChannel);
}

void RGBConfig::attachGreenPin(uint8_t pin)
{
    ledcAttachPin(pin,greenChannel);
}

void RGBConfig::attachBluePin(uint8_t pin)
{
    ledcAttachPin(pin,blueChannel);
}

void RGBConfig::detachRedPin(uint8_t pin)
{
    ledcDetachPin(pin);
}

void RGBConfig::detachGreenPin(uint8_t pin)
{
    ledcDetachPin(pin);
}

void RGBConfig::detachBluePin(uint8_t pin)
{
    ledcDetachPin(pin);
}
