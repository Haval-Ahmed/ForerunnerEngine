/// @file X11Window.cpp
/// @brief X11 specific window creation and management
/// @author Haval Ahmed (Haval-Ahmed)

///////////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
///////////////////////////////////////////////////////////////////////////////
#include "X11Window.h"

///////////////////////////////////////////////////////////////////////////////
/// Standard Libraries
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
/// Platform Libraries
///////////////////////////////////////////////////////////////////////////////
#include <sys/time.h>
#include <unistd.h>
#include <X11/keysymdef.h>

///////////////////////////////////////////////////////////////////////////////
/// External Libraries
///////////////////////////////////////////////////////////////////////////////
#include "glad/glad_glx.h"

namespace ForerunnerEngine
{
    namespace ForerunnerWindow
    {
        FR_API int32_t FR_CALL Initialize(FRWindow* WindowPtr)
        {
            int32_t operationSuccessful = 0;

            if (WindowPtr)
            {
                // Want to call XInitThreads to allow window to run in a separate 
                // thread from render thread
                XInitThreads();
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL Create(FRWindow* WindowPtr, uint32_t Width, uint32_t Height, const char* Title, const char* IconPath)
        {
            int32_t operationSuccessful = 0;

            if (WindowPtr)
            {
                // Open the display
                WindowPtr->XDisplay = XOpenDisplay(NULL);

                if (WindowPtr->XDisplay == NULL)
                {
                    // Can't open display
                }

                WindowPtr->XScreen      = DefaultScreenOfDisplay(WindowPtr->XDisplay);
                WindowPtr->XScreenID    = DefaultScreen(WindowPtr->XDisplay);

                // Check GLX Version before attempting to correct an XWindow
                // as we will require GLX 1.2+
                GLint MajorGLX, MinorGLX = 0;

                // Load GLX extensions before using them
                gladLoadGLX(WindowPtr->XDisplay, WindowPtr->XScreenID);

                // Query GLX Version
                glXQueryVersion(WindowPtr->XDisplay, &MajorGLX, &MinorGLX);

                if (MajorGLX <= 1 && MinorGLX < 2)
                {
                    // Close display
                    XCloseDisplay(WindowPtr->XDisplay);
                }

                // Specify GLX Attributes
                GLint glxAttributes[] = {
                    GLX_X_RENDERABLE    , True,
                    GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
                    GLX_RENDER_TYPE     , GLX_RGBA_BIT,
                    GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
                    GLX_RED_SIZE        , 8,
                    GLX_GREEN_SIZE      , 8,
                    GLX_BLUE_SIZE       , 8,
                    GLX_ALPHA_SIZE      , 8,
                    GLX_DEPTH_SIZE      , 24,
                    GLX_STENCIL_SIZE    , 8,
                    GLX_DOUBLEBUFFER    , True,
                    None
                };

                // Query the frame buffer configuration
                int32_t fbConfiguration;
                GLXFBConfig* FBConfig = glXChooseFBConfig(WindowPtr->XDisplay, WindowPtr->XScreenID, glxAttributes, &fbConfiguration);

                // Ensure we have a frame buffer
                if (FBConfig == 0)
                {
                    // Failed to get frame buffer
                    XCloseDisplay(WindowPtr->XDisplay);
                }

                // Pick the FB config/visual with the most samples per pixel
                int32_t bestFBC                 = -1;
                int32_t worstFBC                = -1;
                int32_t bestNumberOfSamples     = -1;
                int32_t worstNumberOfSamples    = 999;

                for (int32_t i = 0; i < fbConfiguration; ++i) 
                {
                    XVisualInfo *tempVisualInfo = glXGetVisualFromFBConfig(WindowPtr->XDisplay, FBConfig[i]);

                    if (tempVisualInfo != 0) 
                    {
                        int32_t sampleBuffers;
                        int32_t samples;

                        glXGetFBConfigAttrib(WindowPtr->XDisplay, FBConfig[i], GLX_SAMPLE_BUFFERS, &sampleBuffers);
                        glXGetFBConfigAttrib(WindowPtr->XDisplay, FBConfig[i], GLX_SAMPLES       , &samples);

                        if (bestFBC < 0 || (sampleBuffers && samples > bestNumberOfSamples)) 
                        {
                            bestFBC             = i;
                            bestNumberOfSamples = samples;
                        }

                        if (worstFBC < 0 || !sampleBuffers || samples < worstNumberOfSamples)
                        {
                            worstFBC = i;
                        }

                        worstNumberOfSamples = samples;
                    }

                    XFree( tempVisualInfo );
                }

                GLXFBConfig frameBufferConfiguration = FBConfig[ bestFBC ];
                XFree(FBConfig);

                // Assign the chosen FB config
                WindowPtr->XVisual = glXGetVisualFromFBConfig(WindowPtr->XDisplay, frameBufferConfiguration);

                if (WindowPtr->XVisual == 0) 
                {
                    std::cout << "Could not create correct visual window.\n";
                    XCloseDisplay(WindowPtr->XDisplay);
                }

                if (WindowPtr->XScreenID != WindowPtr->XVisual->screen) 
                {
                    std::cout << "screenId(" << WindowPtr->XScreenID << ") does not match visual->screen(" << WindowPtr->XVisual->screen << ").\n";
                    XCloseDisplay(WindowPtr->XDisplay);
                }

                // Configure window attributes
                WindowPtr->XWindowAttributes.border_pixel       = BlackPixel(WindowPtr->XDisplay, WindowPtr->XScreenID);
                WindowPtr->XWindowAttributes.background_pixel   = WhitePixel(WindowPtr->XDisplay, WindowPtr->XScreenID);
                WindowPtr->XWindowAttributes.override_redirect  = True;
                WindowPtr->XWindowAttributes.colormap           = XCreateColormap(WindowPtr->XDisplay, RootWindow(WindowPtr->XDisplay, WindowPtr->XScreenID), WindowPtr->XVisual->visual, AllocNone);
                WindowPtr->XWindowAttributes.event_mask         = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ResizeRedirectMask | ExposureMask | ConfigureNotify | ResizeRequest | PointerMotionMask | PointerMotionHintMask;

                // Create the window with the desired window attributes and visual information
                WindowPtr->XWindow = XCreateWindow(WindowPtr->XDisplay, RootWindow(WindowPtr->XDisplay, WindowPtr->XScreenID), 0, 0, Width, Height, 0, WindowPtr->XVisual->depth, InputOutput, WindowPtr->XVisual->visual, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &WindowPtr->XWindowAttributes);

                // Register the window closing event
                Atom atomWmDeleteWindow = XInternAtom(WindowPtr->XDisplay, "WM_DELETE_WINDOW", False);
                XSetWMProtocols(WindowPtr->XDisplay, WindowPtr->XWindow, &atomWmDeleteWindow, 1);

                // Clear and raise display
                XClearWindow(WindowPtr->XDisplay, WindowPtr->XWindow);
                XMapRaised(WindowPtr->XDisplay, WindowPtr->XWindow);
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL Destroy(FRWindow *WindowPtr)
        {
            int32_t operationSuccessful = 0;

            XFree(WindowPtr->XVisual);
		    XFreeColormap(WindowPtr->XDisplay, WindowPtr->XWindowAttributes.colormap);
		    XDestroyWindow(WindowPtr->XDisplay, WindowPtr->XWindow);
		    XCloseDisplay(WindowPtr->XDisplay);

            return 0;
        }

        FR_API int32_t FR_CALL Resize(FRWindow *WindowPtr, uint32_t Width, uint32_t Height)
        {
            int32_t operationSuccessful = 0;

            // Resize window
            XResizeWindow(WindowPtr->XDisplay, WindowPtr->XWindow, Width, Height);
            
            // Force a redraw
            XClearArea(WindowPtr->XDisplay, WindowPtr->XWindow, 0, 0, Width, Height, true);

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL EnterFullscreen(FRWindow *WindowPtr)
        {
            int32_t operationSuccessful = 0;

            /// Create a xevent to tell the windows manager to transition application from fullscreen to windowed
            XEvent windowedEvent = { 0 };

            /// Get ATOM for fullscreen window
            Atom wmState		= XInternAtom(WindowPtr->XDisplay, "_NET_WSTATE", true);
            Atom displayType[2] = { 0 };

            /// Change from fullscreen to windowed
            displayType[0] = XInternAtom(WindowPtr->XDisplay, "_NET_WSTATE_MAXIMIZED_HORZ", true);
            displayType[1] = XInternAtom(WindowPtr->XDisplay, "_NET_WSTATE_MAXIMIZED_VERT", true);

            // Configure event type
            windowedEvent.type                    = ClientMessage;
            windowedEvent.xclient.window          = WindowPtr->XWindow;
            windowedEvent.xclient.message_type    = wmState;
            windowedEvent.xclient.format          = 32;
            windowedEvent.xclient.data.l[0]       = 1;                /// _NET_WSTATE_ADD = 1, _NET_WSTATE_TOGGLE = 2, _NET_WSTATE_REMOVE = 0
            windowedEvent.xclient.data.l[1]       = displayType[0];   /// _NET_WSTATE_FULLSCREEN
            windowedEvent.xclient.data.l[2]       = displayType[1];   /// Second property
            windowedEvent.xclient.data.l[3]       = 1;                /// Source Indication = Application
            windowedEvent.xclient.data.l[4]       = 0;                /// Unused

            /// Map window
            XMapWindow(WindowPtr->XDisplay, WindowPtr->XWindow);

            /// Send event
            int returnCode = XSendEvent(WindowPtr->XDisplay, DefaultRootWindow(WindowPtr->XDisplay), 0, SubstructureNotifyMask, &windowedEvent);

            /// Flush Display
            XFlush(WindowPtr->XDisplay);            

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL ExitFullscreen(FRWindow *WindowPtr)
        {
            int32_t operationSuccessful = 0;

            /// Create a xevent to tell the windows manager to transition application to toggle fullscreen
            XEvent fullScreenEvent = {0};

            /// Get ATOM for fullscreen window
            Atom wmState		= XInternAtom(WindowPtr->XDisplay, "_NET_WSTATE", false);
            Atom displayType[2] = { XInternAtom(WindowPtr->XDisplay, "_NET_WSTATE_FULLSCREEN", false), None };

            /// Configure event type
            fullScreenEvent.type                    = ClientMessage;
            fullScreenEvent.xclient.window          = WindowPtr->XWindow;
            fullScreenEvent.xclient.message_type    = wmState;
            fullScreenEvent.xclient.format          = 32;
            fullScreenEvent.xclient.data.l[0]       = 2;                /// _NET_WSTATE_TOGGLE
            fullScreenEvent.xclient.data.l[1]       = displayType[0];   /// _NET_WSTATE_FULLSCREEN
            fullScreenEvent.xclient.data.l[2]       = 0;                /// Second property
            fullScreenEvent.xclient.data.l[3]       = 1;                /// Source Indication = Application
            fullScreenEvent.xclient.data.l[4]       = 0;                /// Unused

            /// Map window
            XMapWindow(WindowPtr->XDisplay, WindowPtr->XWindow);

            /// Send event
            int returnCode = XSendEvent(WindowPtr->XDisplay, DefaultRootWindow(WindowPtr->XDisplay), 0, SubstructureNotifyMask, &fullScreenEvent);

            /// Flush Display
            XFlush(WindowPtr->XDisplay);

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL IsWindowClosing(FRWindow *WindowPtr)
        {
            int32_t operationSuccessful = 0;

            // Key system
            KeySym key;

            // Create an X Event
            XEvent eventDescription;

            // Temp variables for QueryPointer
            Window qWindow;
            Window qChild;

            // Mouse input
            int32_t mouseX;
            int32_t mouseY;
            int32_t rootX;
            int32_t rootY;
            uint32_t mask;

            // Enter message loop
            while (true) 
            {
                if (XPending(WindowPtr->XDisplay) > 0) 
                {
                    XNextEvent(WindowPtr->XDisplay, &eventDescription);

                    switch(eventDescription.type)
                    {
                        // Resize the window
                        case ConfigureNotify:
                        {
                            auto newWidth   = eventDescription.xconfigure.width;
                            auto newHeight  = eventDescription.xconfigure.height;
                        }
                        break;

                        case Expose:
                        {
                            auto newWidth   = eventDescription.xconfigure.width;
                            auto newHeight  = eventDescription.xconfigure.height;
                        }
                        break;

                        case ClientMessage:
                        {
                            if (eventDescription.xclient.message_type       == XInternAtom(WindowPtr->XDisplay, "WM_PROTOCOLS", True) &&
                                (Atom)eventDescription.xclient.data.l[0]    == XInternAtom(WindowPtr->XDisplay, "WM_DELETE_WINDOW", True))
                            {
                                // Close window
                            }
                        }
                        break;

                        case MotionNotify:
                        {
                            XQueryPointer(WindowPtr->XDisplay, WindowPtr->XWindow, &qWindow, &qChild, &rootX, &rootY, &mouseX, &mouseY, &mask);
                        }
                        break;

                        case ButtonPress:
                        {
                            auto buttonPressed = eventDescription.xbutton.button;
                            auto xCoordinate = eventDescription.xbutton.x;
                            auto yCoordinate = eventDescription.xbutton.y;
                        }
                        break;

                        case ButtonRelease:
                        {
                            auto buttonPressed = eventDescription.xbutton.button;
                            auto xCoordinate = eventDescription.xbutton.x;
                            auto yCoordinate = eventDescription.xbutton.y;
                        }
                        break;

                        case ResizeRequest:
                        {
                            auto newWidth = eventDescription.xresizerequest.width;
                            auto newHeight = eventDescription.xresizerequest.height;
                        }
                        break;

                        case KeyPress:
                        case KeyRelease:
                        {
                            // Get keypress
                            auto keyCode = eventDescription.xkey.keycode;
                        }
                        break;

                        case MapNotify:
                        {
                            // Set input focus
                            XSetInputFocus(WindowPtr->XDisplay, eventDescription.xmap.window, 0, 0);
                        }
                        break;

                        default:
                            break;

                    }
                }
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL SetWindowTitle(FRWindow* WindowPtr, const char* Title)
        {
            int32_t operationSuccessful = 0;

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL SetWindowIcon(FRWindow* WindowPtr, const char* IconPath)
        {
            int32_t operationSuccessful = 0;

            return operationSuccessful;
        }

        FR_API void FR_CALL RegisterForMouseMoveEvent(MouseMoveCallback callbackFunction)
        {

        }

        FR_API void FR_CALL RegisterForMouseButtonPressed(MouseButtonPressedCallback callbackFunction)
        {

        }

        FR_API void FR_CALL RegisterForMouseButtonReleased(MouseButtonReleasedCallback callbackFunction)
        {

        }

        FR_API void FR_CALL RegisterWindowResizeEvent(WindowResizeCallback callbackFunction)
        {

        }

        FR_API void FR_CALL RegisterMouseScrollWheelEvent(MouseScrollWheelCallback callbackFunction)
        {

        }
    }
}