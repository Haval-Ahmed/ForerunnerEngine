/// @file FRWindow.h
/// @brief Defines a window object for creating and modifying a window object
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef WINDOW_H
#define WINDOW_H

///////////////////////////////////////////////////////////////////////////////
/// Standard Libraries
///////////////////////////////////////////////////////////////////////////////
#include <cstdint>

///////////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
///////////////////////////////////////////////////////////////////////////////
#include "ProjectConfig.h"

namespace ForerunnerEngine
{
    namespace ForerunnerWindow
    {
        // Max number of callback functions - we can resize this value later once we have a better estimate
        constexpr uint32_t MAX_CALLBACK_FUNCTIONS = 256;

        // Declare callback function parameters
        using MouseMoveCallback                 = void(*)(uint32_t MouseCoordinateX, uint32_t MouseCoordinateY);
        using MouseScrollWheelCallback          = void(*)(uint32_t ScrollValue);
        using MouseButtonPressedCallback        = void(*)(uint32_t MouseCoordinateX, uint32_t MouseCoordinateY);
        using MouseButtonReleasedCallback       = void(*)(uint32_t MouseCoordinateX, uint32_t MouseCoordinateY);
        using WindowResizeCallback              = void(*)(uint32_t Width, uint32_t Height);
        using WindowActivatedCallback           = void(*);
        using WindowDeactivatedCallback         = void(*);
        using WindowResolutionChangedCallback   = void(*)(uint32_t Width, uint32_t Height);
        using WindowDragAndDropCallback         = void(*)(const char* FilePath);

        enum MouseButtonEvent : uint32_t
        {
            MOUSE_LBUTTON_PRESSED,
            MOUSE_RBUTTON_PRESSED,
            MOUSE_MBUTTON_PRESSED,
            MOUSE_LBUTTON_RELEASED,
            MOUSE_RBUTTON_RELEASED,
            MOUSE_MBUTTON_RELEASED,
        };

        struct EventWindowType
        {
            int32_t             MouseMoved;
            int32_t             MouseXCoordinate;
            int32_t             MouseYCoordinate;
            int32_t             MouseButtonPressed;
            int32_t             MouseButtonReleased;
            MouseButtonEvent    MouseEvent;
            int32_t             WindowResizeRequested;
            int32_t             WindowDragAndDrop;
            int32_t             KeyboardButtonPressed;
            int32_t             KeyboardButtonReleased;
            int32_t             ControllerAdded;
            int32_t             ControllerLost;
            int32_t             ControllerEvent;
        };
    }
}


#endif // FR_WINDOW_H