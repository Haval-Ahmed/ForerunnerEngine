/// @file OpenGLTexture.h
/// @brief Texture class for OpenGL
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

//////////////////////////////////////////////////////////////////////////
// Forerunner Library
//////////////////////////////////////////////////////////////////////////
#include "OpenGLTexture.h"
#include "ImageIO.h"
#include "Colors.h"

//////////////////////////////////////////////////////////////////////////
// External Library
//////////////////////////////////////////////////////////////////////////
#include "glad/glad.h"

namespace ForerunnerEngine
{
    OpenGLTexture::OpenGLTexture()
    : TextureWidth(0)
    , TextureHeight(0)
    , TextureChannels(0)
    , TextureID(0)
    , TextureWrapSAxis(GL_REPEAT)
    , TextureWrapTAxis(GL_REPEAT)
    , TextureFilterMin(GL_LINEAR)
    , TextureFilterMax(GL_LINEAR)
    , TextureMinmapLevel(GL_LINEAR_MIPMAP_NEAREST)
    {
        glGenTextures(1, &TextureID);
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &TextureID);
    }

    void OpenGLTexture::loadTextureImage(const char* filePath)
    {
        // Image information
        int imageWidth, imageHeight, imageNumChannels;

        // Load image
        unsigned char* imageData = ForerunnerEngine::loadImage(filePath, &imageWidth, &imageHeight, &imageNumChannels);

        // Activate and bind texture
        this->useTexture();

        // If valid data, generate a texture and mipmaps
        if (imageData)
        {
            // Check if image contains alpha channel
            if (ForerunnerEngine::RGB_NUM_CHANNELS == imageNumChannels)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
            }
            else if (ForerunnerEngine::RGBA_NUM_CHANNELS == imageNumChannels)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
            }

            glGenerateMipmap(GL_TEXTURE_2D);
        }

        // Set texture wrapping for S and T axis (X and Y)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapSAxis);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapTAxis);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterMax);

        // Free image data
        ForerunnerEngine::freeImageData(imageData);
    }

    void OpenGLTexture::setTextureWrapping(uint32_t textureWrapSAxis, uint32_t textureWrapTAxis, uint32_t textureBorderColor)
    {
        /// Texture wrapping
        /// GL_REPEAT: The default behavior for textures. Repeats the texture image.
        /// GL_MIRRORED_REPEAT : Same as GL_REPEAT but mirrors the image with each repeat.
        /// GL_CLAMP_TO_EDGE : Clamps the coordinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
        /// GL_CLAMP_TO_BORDER : Coordinates outside the range are now given a user - specified border color.
        /// Texture coordinates = s, t, r == x, y, z
        
        /// Set the texture wrapping/filtering options (on the currently bound texture object)
        TextureWrapSAxis = textureWrapSAxis;
        TextureWrapTAxis = textureWrapTAxis;

        // Activate texture
        this->useTexture();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapSAxis);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapTAxis);

        if (TextureWrapSAxis == GL_CLAMP_TO_BORDER || TextureWrapTAxis == GL_CLAMP_TO_BORDER)
        {
            // Create an array of colors
            float borderColor[] = { 0.0F, 0.0F, 0.0F, 0.0F };

            // Grab rgba values for the border color
            getRGBA(textureBorderColor, borderColor[0], borderColor[1], borderColor[2], borderColor[3]);
            
            // Upload the texture border color
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        }
    }

    void OpenGLTexture::setTextureFiltering(uint32_t textureFilteringMin, uint32_t textureFilteringMax)
    {
        /// Texture filtering
        /// GL_NEAREST
        /// GL_LINEAR
        /// User can specify different options for magnifying and minifying operations (scaling up or down)
        TextureFilterMin = textureFilteringMin;
        TextureFilterMax = textureFilteringMax;

        // Activate texture
        this->useTexture();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterMax);
    }

    void OpenGLTexture::setTextureMinmaps(int32_t minmaplevel)
    {
        /// Minmaps
        /// GL_NEAREST_MIPMAP_NEAREST: takes the nearest mipmap to match the pixel sizeand uses nearest neighbor interpolation for texture sampling.
        /// GL_LINEAR_MIPMAP_NEAREST : takes the nearest mipmap leveland samples using linear interpolation.
        /// GL_NEAREST_MIPMAP_LINEAR : linearly interpolates between the two mipmaps that most closely match the size of a pixeland samples via nearest neighbor interpolation.
        /// GL_LINEAR_MIPMAP_LINEAR : linearly interpolates between the two closest mipmapsand samples the texture via linear interpolation.
        /// Setting minmap filter for mag has no effect because you are downsampling
        
        // Store minmap level
        TextureMinmapLevel = minmaplevel;

        // Activate texture
        this->useTexture();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureMinmapLevel);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    void OpenGLTexture::useTexture()
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureID);
    }
}

#endif