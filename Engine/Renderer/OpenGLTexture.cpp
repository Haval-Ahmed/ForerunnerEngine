/// @file OpenGLTexture.h
/// @brief Texture class for OpenGL
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

//////////////////////////////////////////////////////////////////////////
// Standard Library
//////////////////////////////////////////////////////////////////////////
#include <cstdint> 

namespace ForerunnerEngine
{
    namespace ForerunnerRenderer
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

            void setTextureWrapping(int32_t textureWrappingMode);
            void setTextureFiltering(int32_t textureFiltering);
            void setTextureMinmaps(int32_t minmaplevel);

            void useTexture();
        private:

            int32_t textureWidth;
            int32_t textureHeight;
            int32_t textureChannels;
            int32_t textureID;
        };
    }
}

#endif