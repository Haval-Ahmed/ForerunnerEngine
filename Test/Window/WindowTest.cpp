/// @file WindowTest.cpp
/// @brief Test drive for window library
/// @author Haval Ahmed (Haval-Ahmed)

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <iostream>

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
    #include "Win32Window.h"
#else 
    #include "X11Window.h"
#endif

//////////////////////////////////////////////////////////////////////////
/// Event Loops for specific platforms
//////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
    void Win32EventLoop(ForerunnerEngine::ForerunnerWindow::Window* Win32Window);
#endif

int main()
{
    /// Create a window for this renderer, note this will probably change in the future
    ForerunnerEngine::ForerunnerWindow::FRWindow windowObject;

    // Initialize the window object
    int32_t windowInitialized = ForerunnerEngine::ForerunnerWindow::Initialize(&windowObject);

    // Create the actual window object
    windowInitialized = ForerunnerEngine::ForerunnerWindow::Create(&windowObject, 1280, 720, "Forerunner Window Test", "");

    #ifdef _WIN32
        Win32EventLoop(&windowObject);
    #else
        ForerunnerEngine::ForerunnerWindow::IsWindowClosing(&windowObject);
    #endif

    /// Always Return 0
    return 0;
}

#ifdef _WIN32
    void Win32EventLoop(ForerunnerEngine::ForerunnerWindow::Window* Win32Window)
    {
        /// Create a Message Structure
        MSG Message = { 0 };

        /// Keep receiving messages until WM_Quit is received 
        while (WM_QUIT != Message.message)
        {
            /// Peek the message
            if (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE))
            {
                /// Translate Message
                TranslateMessage(&Message);

                /// Dispatch Message
                DispatchMessage(&Message);
            }
        }
    }
#endif 