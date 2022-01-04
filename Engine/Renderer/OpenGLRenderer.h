/// @file OpenGLRendererWin32.h
/// @brief Defines a opengl win32 renderer object
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <cstdint>

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "BaseRenderer.h"

//////////////////////////////////////////////////////////////////////////
/// GLAD Headers 
//////////////////////////////////////////////////////////////////////////
#include "glad.h"

//////////////////////////////////////////////////////////////////////////
/// GLFW Headers 
//////////////////////////////////////////////////////////////////////////
#include "GLFW/glfw3.h"

namespace ForerunnerEngine
{
    namespace ForerunnerRenderer
    {
        class OpenGLRenderer : public BaseRenderer
        {
        public:
            //////////////////////////////////////////////////////////////////////////
            /// Constructor
            //////////////////////////////////////////////////////////////////////////
            OpenGLRenderer(uint32_t x, uint32_t y, uint32_t width, uint32_t height, GLFWwindow* window);

            //////////////////////////////////////////////////////////////////////////
            /// Virtual Destructor
            //////////////////////////////////////////////////////////////////////////
            virtual ~OpenGLRenderer(void);

            //////////////////////////////////////////////////////////////////////////
            /// Utilties
            //////////////////////////////////////////////////////////////////////////
            virtual void initializeRenderer(void);
            virtual void destroyRenderer(void);

            virtual void makeDeviceContextCurrent(void);
            virtual void configureDeviceContext(void);
            virtual void resetDeviceContext(void);
            virtual void deleteDeviceContext(void);

            virtual void enableMultisampling(uint32_t samplingLevel);
            virtual void enableVSync(void);
            virtual void disableVSync(void);

            virtual void presentAndSwapBuffers(void);

            virtual void enableWireframeMode(void);
            virtual void disableWireframeMode(void);
            virtual void enableDepthTest(void);
            virtual void disableDepthTest(void);

            //////////////////////////////////////////////////////////////////////////
            /// Setters
            //////////////////////////////////////////////////////////////////////////
            virtual void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
            virtual void setSize(uint32_t width, uint32_t height);
            virtual void setXPosition(uint32_t x);
            virtual void setYPosition(uint32_t y);
            virtual void setWidth(uint32_t width);
            virtual void setHeight(uint32_t height);

        protected:

            /// OpenGL Version, Vendor, and Renderer
            int32_t         OpenGLVersion[2] = { 0 };
            const uint8_t*  Vendor;
            const uint8_t*  Renderer;
            GLFWwindow*     Window;
        };
    }
}

#endif	// OPENGLRENDERERWIN32_H