/// @file X11Window.h
/// @brief X11 Window specific window creation and management
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef X11_WINDOW_H
#define X11_WINDOW_H

///////////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
///////////////////////////////////////////////////////////////////////////////
#include "Window.h"

namespace ForerunnerEngine
{
    namespace ForerunnerWindow
    {
        FR_API int32_t FR_CALL Initialize(FRWindow *WindowPtr);
        FR_API int32_t FR_CALL Create(FRWindow *WindowPtr, uint32_t Width, uint32_t Height, const char *Title, const char *IconPath);
        FR_API int32_t FR_CALL Destroy(FRWindow *WindowPtr);
        FR_API int32_t FR_CALL Resize(FRWindow *WindowPtr, uint32_t Width, uint32_t Height);
        FR_API int32_t FR_CALL EnterFullscreen(FRWindow *WindowPtr);
        FR_API int32_t FR_CALL ExitFullscreen(FRWindow *WindowPtr);
        FR_API int32_t FR_CALL IsWindowClosing(FRWindow *WindowPtr);
        FR_API int32_t FR_CALL SetWindowTitle(FRWindow* WindowPtr, const char* Title);
        FR_API int32_t FR_CALL SetWindowIcon(FRWindow* WindowPtr, const char* IconPath);

        FR_API void FR_CALL RegisterForMouseMoveEvent(MouseMoveCallback CallbackFunction);
        FR_API void FR_CALL RegisterForMouseButtonPressed(MouseButtonPressedCallback CallbackFunction);
        FR_API void FR_CALL RegisterForMouseButtonReleased(MouseButtonReleasedCallback CallbackFunction);
        FR_API void FR_CALL RegisterWindowResizeEvent(WindowResizeCallback CallbackFunction);
        FR_API void FR_CALL RegisterMouseScrollWheelEvent(MouseScrollWheelCallback CallbackFunction);
    }
}

#endif // FR_WIN32_WINDOW_H