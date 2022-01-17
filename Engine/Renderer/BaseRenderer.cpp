/// @file BaseRenderer.h
/// @brief Defines a renderer object for creating and modifying a renderer object
/// @author Haval Ahmed (Haval-Ahmed)

//////////////////////////////////////////////////////////////////////////
/// User Defined Library Files
//////////////////////////////////////////////////////////////////////////
#include "BaseRenderer.h"

namespace ForerunnerEngine
{
    BaseRenderer::BaseRenderer()
        : RendererXPosition(0)
        , RendererYPosition(0)
        , RendererWidth(1280)
        , RendererHeight(720)
        , MultisamplingEnabled(false)
        , MultisamplingLevel(4)
        , VSyncEnabled(false)
    {
        /// Empty constructor
    }

    void BaseRenderer::getViewPort(uint32_t& x, uint32_t& y, uint32_t& width, uint32_t& height)
    {
        x       = RendererXPosition;
        y       = RendererYPosition;
        width   = RendererWidth;
        height  = RendererHeight;
    }

    uint32_t BaseRenderer::getXPosition(void)
    {
        return RendererXPosition;
    }

    uint32_t BaseRenderer::getYPosition(void)
    {
        return RendererYPosition;
    }

    uint32_t BaseRenderer::getWidth(void)
    {
        return RendererWidth;
    }

    uint32_t BaseRenderer::getHeight(void)
    {
        return RendererHeight;
    }

    int32_t BaseRenderer::getMultisamplingEnabled(void)
    {
        return MultisamplingEnabled;
    }

    uint32_t BaseRenderer::getMultisamplingLevels(void)
    {
        return MultisamplingLevel;
    }

    int32_t BaseRenderer::getVSyncEnabled(void)
    {
        return VSyncEnabled;
    }
}