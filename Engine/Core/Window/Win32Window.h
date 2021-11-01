/// @file FRWin32Window.h
/// @brief Win32 specific window creation and management
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef WIN32_WINDOW_H
#define WIN32_WINDOW_H

///////////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
///////////////////////////////////////////////////////////////////////////////
#include "Window.h"

namespace ForerunnerEngine
{
    namespace ForerunnerWindow
    {
        FR_API int32_t FR_CALL Initialize(Window *WindowPtr);
        FR_API int32_t FR_CALL Create(Window *WindowPtr, uint32_t Width, uint32_t Height, const char *Title, const char *IconPath);
        FR_API int32_t FR_CALL Destroy(Window *WindowPtr);
        FR_API int32_t FR_CALL Resize(Window *WindowPtr, uint32_t Width, uint32_t Height);
        FR_API int32_t FR_CALL EnterFullscreen(Window *WindowPtr);
        FR_API int32_t FR_CALL ExitFullscreen(Window *WindowPtr);
        FR_API int32_t FR_CALL IsWindowClosing(Window *WindowPtr);
        FR_API int32_t FR_CALL SetWindowTitle(Window* WindowPtr, const char* Title);
        FR_API int32_t FR_CALL SetWindowIcon(Window* WindowPtr, const char* IconPath);
        FR_API int32_t FR_CALL SetWindowStyle(Window* WindowPtr, int32_t WindowStyle);
        FR_API int32_t FR_CALL SetWindowStyleExtended(Window* WindowPtr, int32_t WindowStyleExtended);
        FR_API int32_t FR_CALL SetWindowCursor(Window* WindowPtr, LPWSTR cursorSelection);

        FR_API void FR_CALL RegisterForMouseMoveEvent(MouseMoveCallback CallbackFunction);
        FR_API void FR_CALL RegisterForMouseButtonPressed(MouseButtonPressedCallback CallbackFunction);
        FR_API void FR_CALL RegisterForMouseButtonReleased(MouseButtonReleasedCallback CallbackFunction);
        FR_API void FR_CALL RegisterWindowResizeEvent(WindowResizeCallback CallbackFunction);
        FR_API void FR_CALL RegisterMouseScrollWheelEvent(MouseScrollWheelCallback CallbackFunction);

        // https://docs.microsoft.com/en-us/windows/win32/winmsg/window-styles
        // https://docs.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles
        enum WINDOW_FRAME_TYPE
        {
            NO_WINDOW_FRAME         = WS_VISIBLE | WS_POPUP,
            BASIC_WINDOW_FRAME      = WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SIZEBOX,
            EXTENDED_WINDOW_FRAME   = WS_EX_OVERLAPPEDWINDOW | WS_EX_ACCEPTFILES | WS_EX_TRANSPARENT
        };
    }
}

#endif // FR_WIN32_WINDOW_H