#ifndef RGBCONFIG_H
#define RGBCONFIG_H
#include <inttypes.h>

class RGBConfig
{
public:
    const uint8_t redChannel;
    const uint8_t greenChannel;
    const uint8_t blueChannel;

    const uint32_t frequency;
    const uint8_t resolution;
    
    /// @brief Initialize LEDC channels, set frequency and resolution
    /// @param redChannel 
    /// @param greenChannel 
    /// @param blueChannel 
    /// @param frequency 
    RGBConfig(uint8_t redChannel, uint8_t greenChannel, uint8_t blueChannel, uint32_t frequency);

    /// @brief Sets the red, green, and blue channels to the specified duty cycles
    /// @param red Duty cycle for red
    /// @param green Duty cycle for green
    /// @param blue Duty cycle for blue
    /// @return True if the duty cycles were within the set range
    void setRGB(uint32_t redDuty, uint32_t greenDuty, uint32_t blueDuty);

    /// @brief Attach pin to red channel
    /// @param pin 
    void attachRedPin(uint8_t pin);

    /// @brief Attach pin to green channel
    /// @param pin 
    void attachGreenPin(uint8_t pin);

    /// @brief Attach pin to blue channel
    /// @param pin 
    void attachBluePin(uint8_t pin);

    /// @brief Detach pin to red channel
    /// @param pin 
    void detachRedPin(uint8_t pin);

    /// @brief Detach pin to green channel
    /// @param pin 
    void detachGreenPin(uint8_t pin);

    /// @brief Detach pin to blue channel
    /// @param pin 
    void detachBluePin(uint8_t pin);
};

#endif