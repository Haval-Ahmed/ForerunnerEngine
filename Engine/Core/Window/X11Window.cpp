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
#include <cstring>
#include <climits>
#include <filesystem>

///////////////////////////////////////////////////////////////////////////////
/// Platform Libraries
///////////////////////////////////////////////////////////////////////////////
#include <X11/keysymdef.h>
#include <X11/Xlocale.h>

///////////////////////////////////////////////////////////////////////////////
/// External Libraries
///////////////////////////////////////////////////////////////////////////////
#include "glad/glad_glx.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

///////////////////////////////////////////////////////////////////////////////
/// Function Prototypes
///////////////////////////////////////////////////////////////////////////////
uint32_t createRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
uint32_t convertRGBAToARGBA(uint32_t rgba);

namespace ForerunnerEngine
{
    namespace ForerunnerWindow
    {
        struct MWM_HINTS
        {
            unsigned long   Flags;
            unsigned long   Functions;
            unsigned long   Decorations;
            long            InputMode;
            unsigned long   StatusMode;

            MWM_HINTS()
            {
                Flags       = (1L << 1);
                Functions   = 0;
                Decorations = 1; // Have a boarder by default
                InputMode   = 0;
                StatusMode  = 0;
            }
        };

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
                    GLX_DOUBLEBUFFER    , True,
                    GLX_RED_SIZE        , 8,
                    GLX_GREEN_SIZE      , 8,
                    GLX_BLUE_SIZE       , 8,
                    GLX_ALPHA_SIZE      , 8,
                    GLX_DEPTH_SIZE      , 24,
                    GLX_STENCIL_SIZE    , 8,
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
                WindowPtr->XWindowAttributes.event_mask         = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ResizeRedirectMask | ExposureMask | ConfigureNotify | ResizeRequest | PointerMotionMask | PointerMotionHintMask | StructureNotifyMask | EnterWindowMask | LeaveWindowMask;

                // Create the window with the desired window attributes and visual information
                WindowPtr->XWindow = XCreateWindow(WindowPtr->XDisplay, RootWindow(WindowPtr->XDisplay, WindowPtr->XScreenID), 0, 0, Width, Height, 0, WindowPtr->XVisual->depth, InputOutput, WindowPtr->XVisual->visual, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &WindowPtr->XWindowAttributes);

                // Register the window closing event
                WindowPtr->XAtomDeleteWindow = XInternAtom(WindowPtr->XDisplay, "WM_DELETE_WINDOW", False);
                XSetWMProtocols(WindowPtr->XDisplay, WindowPtr->XWindow, &WindowPtr->XAtomDeleteWindow, 1);

                // Enable drag and drop capability
                WindowPtr->XAtomXdndAware   = XInternAtom(WindowPtr->XDisplay, "XdndAware", False);
                Atom XDragAndDropVersion    = 5;
                XChangeProperty(WindowPtr->XDisplay, WindowPtr->XWindow, WindowPtr->XAtomXdndAware, XA_ATOM, 32, PropModeReplace, (uint8_t*)&XDragAndDropVersion, 1);

                // Store atoms for drag and drop capability
                WindowPtr->XAtomXdndPosition    = XInternAtom(WindowPtr->XDisplay, "XdndPosition", False);
                WindowPtr->XAtomXdndDrop        = XInternAtom(WindowPtr->XDisplay, "XdndDrop", False);
                WindowPtr->XAtomXdndActionCopy  = XInternAtom(WindowPtr->XDisplay, "XdndActionCopy", False);
                WindowPtr->XAtomXdndStatus      = XInternAtom(WindowPtr->XDisplay, "XdndStatus", False);
                WindowPtr->XAtomXdndFinished    = XInternAtom(WindowPtr->XDisplay, "XdndFinished", False);

                // Clear and raise display
                XClearWindow(WindowPtr->XDisplay, WindowPtr->XWindow);
                XMapRaised(WindowPtr->XDisplay, WindowPtr->XWindow);

                // Set window code
                SetWindowTitle(WindowPtr, Title);
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
            int32_t operationSuccessful = 1;

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
            while (XPending(WindowPtr->XDisplay) > 0) 
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
                            operationSuccessful = 0;
                        }
                        else if (eventDescription.xclient.message_type == WindowPtr->XAtomXdndPosition)
                        {
                            // Drag and drop event inside the window

                            // Recover the position
                            int xWindow, yWindow;
                            int xRoot   = eventDescription.xclient.data.l[2] >> 16;
                            int yRoot   = eventDescription.xclient.data.l[2] & 0xFFFF;
                            Window root = DefaultRootWindow(WindowPtr->XDisplay);
                            Window child;

                            // Convert coordinates
                            XTranslateCoordinates(WindowPtr->XDisplay, root, WindowPtr->XWindow, xRoot, yRoot, &xWindow, &yWindow, &child);

                            // Reply that we are ready to copy the dragged data
                            XEvent reply = { 0 };

                            reply.type                  = ClientMessage;
                            reply.xclient.window        = WindowPtr->XWindow;
                            reply.xclient.message_type  = WindowPtr->XAtomXdndStatus;
                            reply.xclient.format        = 32;
                            reply.xclient.data.l[0]     = WindowPtr->XWindow;
                            reply.xclient.data.l[1]     = 1; // Always accept the dnd with no rectangle
                            reply.xclient.data.l[2]     = 0; // Specify an empty rectangle
                            reply.xclient.data.l[3]     = 0;
                            reply.xclient.data.l[4]     = WindowPtr->XAtomXdndActionCopy;

                            // Send the event
                            XSendEvent(WindowPtr->XDisplay, eventDescription.xclient.data.l[0], False, NoEventMask, &reply);

                            // Flush the data
                            XFlush(WindowPtr->XDisplay);

                        }
                        else if (eventDescription.xclient.message_type == WindowPtr->XAtomXdndDrop)
                        {
                            // Item dropped in the window
                            // Store the source of the drag and drop
                            WindowPtr->XAtomXdndStatus = eventDescription.xclient.data.l[0];

                            // Ask for a conversion of the selection. This will trigger a SelectioNotify event later.
                            Atom xdndSelectionAtom = XInternAtom(WindowPtr->XDisplay, "XdndSelection", False);

                            // Convert the selection
                            XConvertSelection(WindowPtr->XDisplay, xdndSelectionAtom, XInternAtom(WindowPtr->XDisplay, "UTF8_STRING", False), xdndSelectionAtom, WindowPtr->XWindow, CurrentTime);
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

                    case SelectionNotify:
                    {
                        if (!eventDescription.xselection.property || WindowPtr->XAtomXdndStatus)
                        {
                            return 0;
                        }

                        // Get file name that was dragged onto window
                        char*   fileData;
                        Atom    fileType;
                        int32_t formatType;
                        unsigned long itemCount;
                        unsigned long bytesAfter;

                        // Get winodw property
                        XGetWindowProperty(WindowPtr->XDisplay, WindowPtr->XWindow, eventDescription.xselection.property, 0, LONG_MAX, False, eventDescription.xselection.target, &fileType, &formatType, &itemCount, &bytesAfter, (uint8_t**)&fileData);

                        // Free data after using
                        XFree(fileData);

                        // Send a reply to the source that we parsed the drag and drop event
                        XEvent replyEvent               = { 0 };
                        replyEvent.type                 = ClientMessage;
                        replyEvent.xclient.window       = WindowPtr->XAtomXdndStatus;
                        replyEvent.xclient.message_type = WindowPtr->XAtomXdndFinished;
                        replyEvent.xclient.format       = 32;
                        replyEvent.xclient.data.l[0]    = (long)WindowPtr->XDisplay;
                        replyEvent.xclient.data.l[1]    = itemCount;
                        replyEvent.xclient.data.l[2]    = WindowPtr->XAtomXdndActionCopy;

                        // Send event
                        XSendEvent(WindowPtr->XDisplay, WindowPtr->XWindow, False, NoEventMask, &replyEvent);

                        // Flush display
                        XFlush(WindowPtr->XDisplay);

                        // Reset status
                        WindowPtr->XAtomXdndStatus = 0;
                    }
                    break;

                    default:
                        break;

                }
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL SetWindowTitle(FRWindow* WindowPtr, const char* Title)
        {
            int32_t operationSuccessful = 0;

            // Create an atom for the wm name property
            Atom wmName         = XInternAtom(WindowPtr->XDisplay, "_NET_WM_NAME", False);
            Atom wmNameIcon     = XInternAtom(WindowPtr->XDisplay, "_NET_WM_ICON_NAME", False);
            Atom UTF8_STRING    = XInternAtom(WindowPtr->XDisplay, "UTF8_STRING", False);

            // Also create a class hint to ensure task bar icon name is set
            XClassHint *classHint = XAllocClassHint();
    
            if (classHint)
            {
                classHint->res_name = classHint->res_class = (char *)Title;
                XSetClassHint(WindowPtr->XDisplay, WindowPtr->XWindow, classHint);
                XFree(classHint);
            }

            // Change property
            XChangeProperty(WindowPtr->XDisplay, WindowPtr->XWindow, wmName, UTF8_STRING, 8, 0, (const uint8_t*)Title, strlen(Title));
            XChangeProperty(WindowPtr->XDisplay, WindowPtr->XWindow, wmNameIcon, UTF8_STRING, 8, 0, (const uint8_t*)Title, strlen(Title));
	        XChangeProperty(WindowPtr->XDisplay, WindowPtr->XWindow, XA_WM_ICON_NAME, XA_STRING, 8, 0, (const uint8_t*)Title, strlen(Title));

            // Flush the display
            XFlush(WindowPtr->XDisplay);

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL SetWindowIcon(FRWindow* WindowPtr, const char* IconPath)
        {
            int32_t operationSuccessful = 0;

            // image info
            int32_t imageWidth;
            int32_t imageHeight;
            int32_t imageNumChannels;

            // Data needs to be formated in the following format: ARGB8888
            uint8_t *imageData = stbi_load(IconPath, &imageWidth, &imageHeight, &imageNumChannels, STBI_rgb_alpha);

            // Atom for icon
            Atom wmIcon = XInternAtom(WindowPtr->XDisplay, "_NET_WM_ICON", False);

            // Create the prop data
            long* iconData;
            int32_t iconSize        = (imageWidth * imageHeight);
            int32_t iconSizeLong    = 2 + iconSize;
            iconData                = new long[iconSizeLong];

            // Store width and height in first two elements and then actual image data
            iconData[0] = imageWidth;
            iconData[1] = imageHeight;

            // index counter
            int32_t imageCounter = 0;

            // Copy uint8_t into long array just to cast back into uint8_t
            for (size_t i = 2; i < iconSize; i++)
            {
                // Create RGBA pixel
                uint32_t rgbaPixel = createRGBA(imageData[imageCounter], imageData[imageCounter + 1], imageData[imageCounter + 2], imageData[imageCounter + 3]);

                // Convert from RGBA to ARGB 
                iconData[i] = (long)rgbaPixel;

                // Increment counter
                imageCounter += imageNumChannels;
            }

            // Assign new window icon
            XChangeProperty(WindowPtr->XDisplay, WindowPtr->XWindow, wmIcon, XA_CARDINAL, 32, PropModeReplace, (uint8_t*)iconData, iconSizeLong);

            // Flush the display
            XFlush(WindowPtr->XDisplay);

            // Free image data
            stbi_image_free(imageData);

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL EnableWindowBoarder(FRWindow* WindowPtr)
        {
            int32_t operationSuccessful = 0;

            // Create a WM_Hints struct
            MWM_HINTS windowBoarder;

            // Grab the atom
            Atom WM_HINTS = XInternAtom(WindowPtr->XDisplay, "_MOTIF_WM_HINTS", True);

            // Change to enable window boarder
            XChangeProperty(WindowPtr->XDisplay, WindowPtr->XWindow, WM_HINTS, WM_HINTS, 32, PropModeReplace, (uint8_t*)&windowBoarder, sizeof(MWM_HINTS) / sizeof(long));
                
            // Flush the display
            XFlush(WindowPtr->XDisplay);

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL RemoveWindowBoarder(FRWindow* WindowPtr)
        {
            int32_t operationSuccessful = 0;

            // Create a WM_Hints struct
            MWM_HINTS windowBoarder;

            // Disable boarder
            windowBoarder.Decorations = 0;

            // Grab the atom
            Atom WM_HINTS = XInternAtom(WindowPtr->XDisplay, "_MOTIF_WM_HINTS", True);

            // Change to enable window boarder
            XChangeProperty(WindowPtr->XDisplay, WindowPtr->XWindow, WM_HINTS, WM_HINTS, 32, PropModeReplace, (uint8_t*)&windowBoarder, sizeof(MWM_HINTS) / sizeof(long));

            // Flush the display
            XFlush(WindowPtr->XDisplay);

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

uint32_t createRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    uint32_t pixel = 0x00000000;

    pixel |= (static_cast<uint32_t>(alpha) << 24) & 0xFF000000; //AA______
    pixel |= (static_cast<uint32_t>(red)   << 16) & 0x00FF0000; //__RR____
    pixel |= (static_cast<uint32_t>(green) << 8)  & 0x0000FF00; //____GG__
    pixel |= (static_cast<uint32_t>(blue) & 0x000000FF);        //______BB

    return pixel;
}

uint32_t convertRGBAToARGBA(uint32_t rgba)
{
    // Source is in format: 0xAARRGGBB
    // Return value is in format:  0xBBGGRRAA
    return ((rgba   & 0xFF000000) >> 24)    |   //______AA
            ((rgba  & 0x00FF0000) >> 8)     |   //____RR__
            ((rgba  & 0x0000FF00) << 8)     |   //__GG____
            ((rgba  & 0x000000FF) << 24);       //BB______
}