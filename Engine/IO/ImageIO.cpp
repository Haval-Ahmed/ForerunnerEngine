//////////////////////////////////////////////////////////////////////////
/// Image Loading Library
//////////////////////////////////////////////////////////////////////////
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//////////////////////////////////////////////////////////////////////////
/// Local Libraries
//////////////////////////////////////////////////////////////////////////
#include "ImageIO.h"

namespace ForerunnerEngine
{
    uint8_t* loadImage(const char* filePath, int32_t* imageWidth, int32_t* imageHeight, int32_t* imageNumChannels)
    {
        return stbi_load(filePath, imageWidth, imageHeight, imageNumChannels, 0);
    }

    void freeImageData(uint8_t* imageData)
    {
        if (imageData != nullptr)
        {
            stbi_image_free(imageData);
        }
    }
}