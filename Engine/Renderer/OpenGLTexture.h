/// @file OpenGLTexture.h
/// @brief Texture class for OpenGL
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef OPENGLTEXTURE_H
#define OPENGLTEXTURE_H

//////////////////////////////////////////////////////////////////////////
// Standard Library
//////////////////////////////////////////////////////////////////////////
#include <cstdint> 

namespace ForerunnerEngine
{
    class OpenGLTexture
    {
    public:

        //////////////////////////////////////////////////////////////////////////
        /// Constructor
        //////////////////////////////////////////////////////////////////////////
        OpenGLTexture();

        //////////////////////////////////////////////////////////////////////////
        /// Virtual destructor
        //////////////////////////////////////////////////////////////////////////
        virtual ~OpenGLTexture();

        //////////////////////////////////////////////////////////////////////////
        /// Utilties
        //////////////////////////////////////////////////////////////////////////
        void loadTextureImage(const char* filePath);
        void setTextureWrapping(uint32_t textureWrapSAxis, uint32_t textureWrapTAxis, uint32_t textureBorderColor = 0xFFFFFFFF);
        void setTextureFiltering(uint32_t textureFilteringMin, uint32_t textureFilteringMax);
        void setTextureMinmaps(int32_t minmaplevel);
        void useTexture(void);

    private:

        uint32_t TextureWidth;
        uint32_t TextureHeight;
        uint32_t TextureChannels;
        uint32_t TextureID;
        uint32_t TextureWrapSAxis; // X Axis Texture Wrapping
        uint32_t TextureWrapTAxis; // Y Axis Texture Wrapping
        uint32_t TextureFilterMin;
        uint32_t TextureFilterMax;
        uint32_t TextureMinmapLevel;
    };
}

#endif