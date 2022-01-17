/// @file Colors.h
/// @brief Defines a set of colors for easy usage
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef COLORS_H
#define COLORS_H

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <cstdint>

namespace ForerunnerEngine
{
    // Common colors
    constexpr uint32_t BLACK    = 0x0;
    constexpr uint32_t WHITE    = 0x0;
    constexpr uint32_t BLUE     = 0x0;
    constexpr uint32_t CYAN     = 0x0;
    constexpr uint32_t YELLOW   = 0x0;
    constexpr uint32_t RED      = 0x0;
    constexpr uint32_t GREEN    = 0x0;
    constexpr uint32_t PURPLE   = 0x0;

    // Conversions between differents ranges (0.0 - 1.0) - (0 - 255)
    constexpr float FLOAT_RANGE = 1.0F / 255.0F;

    // Utilities
    uint32_t createRGBA(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha)
    {
        // Format is 0xAARRGGBB
        uint32_t color = 0x00;

        color = ((alpha & 0xFF000000) << 24) |
                ((red   & 0x00FF0000) << 16) |
                ((green & 0x0000FF00) << 8)  |
                ((blue  & 0x000000FF));
        
        return color;
    }

    uint32_t createARGB(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha)
    {
        // Format is 0xBBGGRRAA
        uint32_t color = 0x00;

        color = ((alpha & 0xFF000000) >> 24) |
                ((red   & 0x00FF0000) >> 8)  |
                ((green & 0x0000FF00) >> 8)  |
                ((blue  & 0x000000FF) << 24);
        
        return color;
    }

    void getRGBA(uint32_t color, uint8_t &red, uint8_t &green, uint8_t &blue, uint8_t &alpha)
    {
        red     = color & 0x00FF0000;
        green   = color & 0x0000FF00;
        blue    = color & 0x000000FF;
        alpha   = color & 0xFF000000;
    }

    void getRGBA(uint32_t color, float &red, float &green, float &blue, float &alpha)
    {
        red     = (color & 0x00FF0000) * FLOAT_RANGE;
        green   = (color & 0x0000FF00) * FLOAT_RANGE;
        blue    = (color & 0x000000FF) * FLOAT_RANGE;
        alpha   = (color & 0xFF000000) * FLOAT_RANGE;
    }
}

#endif