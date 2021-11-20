/// @file FRWindow.h
/// @brief Defines a window object for creating and modifying a window object
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef WINDOW_H
#define WINDOW_H

///////////////////////////////////////////////////////////////////////////////
/// Standard Libraries
///////////////////////////////////////////////////////////////////////////////
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/// Platform Libraries
///////////////////////////////////////////////////////////////////////////////
#if _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <Windows.h>
#elif LINUX
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xatom.h>
#endif

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

        struct MonitorInformation
        {
            #if _WIN32
                RECT MonitorRect;
            #endif 

            int32_t     MonitorScaleFactor;
            uint32_t    MonitorDPI;
        };

        struct FRWindow
        {
            uint32_t            ClientWidth;
            uint32_t            ClientHeight;
            uint32_t            NumberOfMonitors;
            MonitorInformation  MonitorInfo;
            int32_t             WindowMaximized;
            int32_t             MaxIconWidth;
            int32_t             MaxIconHeight;

            #if _WIN32
                HDC         WindowDevice;
                HINSTANCE   WindowInstance;
                HWND        WindowHandle;
                RECT        ClientWindowRect;
                int32_t     WindowStyle;
                int32_t     ExtendedWindowStyle;
            #else 
                Display*                XDisplay;
                Window                  XWindow;
                Screen*                 XScreen;
                int32_t                 XScreenID;
                XVisualInfo*            XVisual;
                XSetWindowAttributes    XWindowAttributes;
                Atom                    XAtomDeleteWindow;
                Atom                    XAtomXdndAware;
                Atom                    XAtomXdndPosition;
                Atom                    XAtomXdndDrop;
                Atom                    XAtomXdndActionCopy;
                Atom                    XAtomXdndStatus;
                Atom                    XAtomXdndFinished;
                Atom                    XAtomXndnSource;
            #endif

            MouseMoveCallback           MouseMoveCallbacks[MAX_CALLBACK_FUNCTIONS];
            MouseScrollWheelCallback    MouseScrollWheelCallbacks[MAX_CALLBACK_FUNCTIONS];
            MouseButtonPressedCallback  MouseButtonPressedCallbacks[MAX_CALLBACK_FUNCTIONS];

        };

        namespace CursorType
        {
            #if _WIN32
                LPWSTR ARROW_CURSOR       = IDC_ARROW;
                LPWSTR IBEAM_CURSOR       = IDC_IBEAM;
                LPWSTR WAIT_CURSOR        = IDC_WAIT;
                LPWSTR CROSS_CURSOR       = IDC_CROSS;
                LPWSTR UPARROW_CURSOR     = IDC_UPARROW;
                LPWSTR SIZENWSE_CURSOR    = IDC_SIZENWSE;
                LPWSTR SIZENESW_CURSOR    = IDC_SIZENESW;
                LPWSTR SIZEWE_CURSOR      = IDC_SIZEWE;
                LPWSTR SIZENS_CURSOR      = IDC_SIZENS;
                LPWSTR SIZEALL_CURSOR     = IDC_SIZEALL;
                LPWSTR NO_CURSOR          = IDC_NO;
                LPWSTR HAND_CURSOR        = IDC_HAND;
                LPWSTR APPSTARTING_CURSOR = IDC_APPSTARTING;
                LPWSTR HELP_CURSOR        = IDC_HELP;
                LPWSTR PIN_CURSOR         = IDC_PIN;
                LPWSTR PERSON_CURSOR      = IDC_PERSON;
            #endif
        };

        extern FR_API int32_t FR_CALL Initialize(FRWindow *WindowPtr);
        extern FR_API int32_t FR_CALL Create(FRWindow *WindowPtr, uint32_t Width, uint32_t Height, const char *Title = "", const char *IconPath = "");
        extern FR_API int32_t FR_CALL Destroy(FRWindow *WindowPtr);
        extern FR_API int32_t FR_CALL Resize(FRWindow *WindowPtr, uint32_t Width, uint32_t Height);
        extern FR_API int32_t FR_CALL EnterFullscreen(FRWindow *WindowPtr);
        extern FR_API int32_t FR_CALL ExitFullscreen(FRWindow *WindowPtr);
        extern FR_API int32_t FR_CALL IsWindowClosing(FRWindow *WindowPtr);
        extern FR_API int32_t FR_CALL SetWindowTitle(FRWindow* WindowPtr, const char *Title);
        extern FR_API int32_t FR_CALL SetWindowIcon(FRWindow* WindowPtr, const char *IconPath);

        #if _WIN32
            extern FR_API int32_t FR_CALL SetWindowCursor(FRWindow* WindowPtr, LPWSTR cursorSelection);
        #endif

        extern FR_API void FR_CALL RegisterForMouseMoveEvent(MouseMoveCallback CallbackFunction);
        extern FR_API void FR_CALL RegisterForMouseButtonPressed(MouseButtonPressedCallback CallbackFunction);
        extern FR_API void FR_CALL RegisterForMouseButtonReleased(MouseButtonReleasedCallback CallbackFunction);
        extern FR_API void FR_CALL RegisterWindowResizeEvent(WindowResizeCallback CallbackFunction);
        extern FR_API void FR_CALL RegisterMouseScrollWheelEvent(MouseScrollWheelCallback CallbackFunction);
    }
}


#endif // FR_WINDOW_H