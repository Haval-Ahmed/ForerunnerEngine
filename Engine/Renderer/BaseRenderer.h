/// @file BaseRenderer.h
/// @brief Defines a renderer object for creating and modifying a renderer object
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef BASERENDERER_H
#define BASERENDERER_H

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <cstdint>

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "Window.h"

namespace ForerunnerEngine
{
    namespace ForerunnerRenderer
    {
        class BaseRenderer
        {
        public:
            //////////////////////////////////////////////////////////////////////////
            /// Constructor
            //////////////////////////////////////////////////////////////////////////
            BaseRenderer();

            //////////////////////////////////////////////////////////////////////////
            /// Virtual destructor
            //////////////////////////////////////////////////////////////////////////
            virtual ~BaseRenderer() {};

            //////////////////////////////////////////////////////////////////////////
            /// Utilties
            //////////////////////////////////////////////////////////////////////////
            virtual void initializeRenderer(void)                       = 0;
            virtual void destroyRenderer(void)                          = 0;
            virtual void configureDeviceContext(void)                   = 0;
            virtual void resetDeviceContext(void)                       = 0;
            virtual void deleteDeviceContext(void)                      = 0;
            virtual void enableMultisampling(uint32_t samplingLevel)    = 0;
            virtual void enableVSync(void)                              = 0;
            virtual void disableVSync(void)                             = 0;
            virtual void presentAndSwapBuffers(void)                    = 0;

            //////////////////////////////////////////////////////////////////////////
            /// Setters
            //////////////////////////////////////////////////////////////////////////
            virtual void setViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)   = 0;
            virtual void setXPosition(uint32_t x)                                               = 0;
            virtual void setYPosition(uint32_t y)                                               = 0;
            virtual void setWidth(uint32_t width)                                               = 0;
            virtual void setHeight(uint32_t height)                                             = 0;

            //////////////////////////////////////////////////////////////////////////
            /// Getters
            //////////////////////////////////////////////////////////////////////////
            virtual void        getViewPort(uint32_t& x, uint32_t& y, uint32_t& width, uint32_t& height);
            virtual uint32_t    getXPosition(void);
            virtual uint32_t    getYPosition(void);
            virtual uint32_t    getWidth(void);
            virtual uint32_t    getHeight(void);
            virtual int32_t     getMultisamplingEnabled(void);
            virtual uint32_t    getMultisamplingLevels(void);
            virtual int32_t     getVSyncEnabled(void);

        protected:

            //////////////////////////////////////////////////////////////////////////
            ///	Renderer Variables
            //////////////////////////////////////////////////////////////////////////
            uint32_t    RendererWidth;
            uint32_t    RendererHeight;
            uint32_t    RendererXPosition;
            uint32_t    RendererYPosition;
            int32_t     MultisamplingEnabled;
            uint32_t    MultisamplingLevel;
            int32_t     VSyncEnabled;
        };
    }
}

#endif  /// BASERENDERER_H