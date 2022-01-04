/// @file Renderer.h
/// @brief Common enums for renderer types
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef RENDERER_H
#define RENDERER_H

//////////////////////////////////////////////////////////////////////////
// Standard Library
//////////////////////////////////////////////////////////////////////////
#include <cstdint> 

namespace ForerunnerEngine
{
    enum class RENDERER_TYPE : int32_t 
    { 
        SOFTWARE_RENDERER       = 0, 
        OPENGL_CORE_RENDERER    = 1,
        D3D11_RENDERER          = 2,
        VULKAN_RENDERER         = 3,
        D3D12_RENDERER          = 4,
        TOTAL_RENDERERS
    };
}

#endif /// RENDERER_H

