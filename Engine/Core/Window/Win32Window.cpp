/// @file FRWin32Window.cpp
/// @brief Win32 specific window creation and management
/// @author Haval Ahmed (Haval-Ahmed)

///////////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
///////////////////////////////////////////////////////////////////////////////
#include "Win32Window.h"

///////////////////////////////////////////////////////////////////////////////
/// Standard Libraries
///////////////////////////////////////////////////////////////////////////////
#include <string>

///////////////////////////////////////////////////////////////////////////////
/// Platform Libraries
///////////////////////////////////////////////////////////////////////////////
#include <shellapi.h>
#include <ShellScalingApi.h>
#include <windowsx.h>

///////////////////////////////////////////////////////////////////////////////
/// Function Prototypes
///////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

namespace ForerunnerEngine
{
    namespace ForerunnerWindow
    {
        FR_API int32_t FR_CALL Initialize(Window* WindowPtr)
        {
            int32_t operationSuccessful = 0;

            if (WindowPtr)
            {
                // Grab common system metrics for window, monitors, etc...
                WindowPtr->NumberOfMonitors = GetSystemMetrics(SM_CMONITORS);
                WindowPtr->MaxIconWidth     = GetSystemMetrics(SM_CXICON);
                WindowPtr->MaxIconHeight    = GetSystemMetrics(SM_CYICON);

                // Should be no issues during initialization
                operationSuccessful = 1;
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL Create(Window* WindowPtr, uint32_t Width, uint32_t Height, const char* Title, const char* IconPath)
        {
            int32_t operationSuccessful = 0;

            // Local variable for error handling Win32 functions
            DWORD errorCode = 0;

            if (WindowPtr)
            {
                // Store surface information
                WindowPtr->ClientWidth  = Width;
                WindowPtr->ClientHeight = Height;

                // Create wide string because unicode requires a wstring
                std::wstring wWindowName;
                std::wstring wWindowIcon;

                // Convert strings to wstrings
                for (size_t i = 0; i < strlen(Title); i++)
                {
                    wWindowName += Title[i];
                }

                if (IconPath)
                {
                    for (size_t i = 0; i < strlen(IconPath); i++)
                    {
                        wWindowIcon += IconPath[i];
                    }
                }

                // Grab the module handle
                WindowPtr->WindowInstance = GetModuleHandle(nullptr);

                // Create a WNDCLASS
                WNDCLASSEX windowClass = { 0 };

                // Set attributes for class
                windowClass.cbClsExtra      = 0;                                                /// Extra Bytes To Allocate For Window 
                windowClass.cbWndExtra      = 0;                                                /// Extra Bytes To Allocate For Window Instance
                windowClass.cbSize          = sizeof(WNDCLASSEX);                               /// Size of window in bytes
                windowClass.hbrBackground   = HBRUSH(COLOR_WINDOW + 1);                         /// Background color
                windowClass.hCursor         = LoadCursor(WindowPtr->WindowInstance, IDC_ARROW); /// Use default arrow cursor for now
                windowClass.hInstance       = WindowPtr->WindowInstance;                        /// Handle to application instance
                windowClass.lpfnWndProc     = WndProc;                                          /// Windows Callback Function
                windowClass.lpszClassName   = wWindowName.c_str();
                windowClass.lpszMenuName    = nullptr;
                windowClass.style           = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

                // Check if we need to set a window icon
                if (IconPath)
                {
                    windowClass.hIconSm = NULL;
                    windowClass.hIcon   = (HICON)LoadImage( NULL,
                                                            wWindowIcon.c_str(),
                                                            IMAGE_ICON,
                                                            0,
                                                            0,
                                                            LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
                }

                // Register Class
                if (RegisterClassEx(&windowClass))
                {
                    // Configure the window rect
                    WindowPtr->ClientWindowRect = { 0, 0, static_cast<long>(Width), static_cast<long>(Height) };

                    /// Update window rectangle to give us the actual requested size of the client
                    if (!AdjustWindowRectEx(&WindowPtr->ClientWindowRect, BASIC_WINDOW_FRAME, false, EXTENDED_WINDOW_FRAME))
                    {
                        // TODO - Add error to log file
                        errorCode = GetLastError();
                    }

                    /// Create the Window
                    WindowPtr->WindowHandle = CreateWindowEx(   EXTENDED_WINDOW_FRAME,
                                                                wWindowName.c_str(),
                                                                LPCWSTR(wWindowName.c_str()),
                                                                BASIC_WINDOW_FRAME,
                                                                CW_USEDEFAULT,
                                                                CW_USEDEFAULT,
                                                                WindowPtr->ClientWindowRect.right  - WindowPtr->ClientWindowRect.left,
                                                                WindowPtr->ClientWindowRect.bottom - WindowPtr->ClientWindowRect.top,
                                                                nullptr,
                                                                nullptr,
                                                                WindowPtr->WindowInstance,
                                                                WindowPtr);  // Pass window object pointer to WndProc to allow us to access it

                    // Check if window was created without errors
                    if (WindowPtr->WindowHandle)
                    {
                        // at this point we have successfully created a window 
                        operationSuccessful = 1;

                        /// Grab hardware monitor
                        HMONITOR hardwareMonitor = MonitorFromWindow(WindowPtr->WindowHandle, MONITOR_DEFAULTTONEAREST);

                        // Struct that contains monitor information
                        MONITORINFOEX monitorInformationEx = { 0 };

                        // Size cbSize to approriate size
                        monitorInformationEx.cbSize = sizeof(monitorInformationEx);

                        // Get monitor information
                        if (GetMonitorInfo(hardwareMonitor, &monitorInformationEx))
                        {
                            WindowPtr->MonitorInfo.MonitorRect.bottom   = monitorInformationEx.rcMonitor.bottom;
                            WindowPtr->MonitorInfo.MonitorRect.top      = monitorInformationEx.rcMonitor.top;
                            WindowPtr->MonitorInfo.MonitorRect.right    = monitorInformationEx.rcMonitor.right;
                            WindowPtr->MonitorInfo.MonitorRect.left     = monitorInformationEx.rcMonitor.left;
                        }
                        else
                        {
                            // TODO - Add error to log file
                            errorCode = GetLastError();
                        }

                        // Get monitor scale factor
                        DEVICE_SCALE_FACTOR deviceScaleFactor;

                        if (GetScaleFactorForMonitor(hardwareMonitor, &deviceScaleFactor) == S_OK)
                        {
                            // Cast the scale factor to an int
                            WindowPtr->MonitorInfo.MonitorScaleFactor = static_cast<int32_t>(deviceScaleFactor);
                        }
                        else
                        {
                            // TODO - Add error to log file
                            errorCode = GetLastError();
                        }

                        // Get window/monitor DPI factor
                        WindowPtr->MonitorInfo.MonitorDPI = GetDpiForWindow(WindowPtr->WindowHandle);

                        // Allow drag and drop for the window
                        DragAcceptFiles(WindowPtr->WindowHandle, true);

                        /// Place window text
                        if (!SetWindowText(WindowPtr->WindowHandle, LPCWSTR(wWindowName.c_str())))
                        {
                            // TODO - Add error to log file
                            errorCode = GetLastError();
                        }

                        // Update Window
                        if (!UpdateWindow(WindowPtr->WindowHandle))
                        {
                            // TODO - Add error to log file
                            errorCode = GetLastError();
                        }
                    }
                }
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL Destroy(Window* WindowPtr)
        {
            int32_t operationSuccessful = 0;

            // Destroy Window and Window Instance
            if (WindowPtr->WindowHandle != nullptr)
            {
                DestroyWindow(WindowPtr->WindowHandle);
            }

            // Set to nullptr
            WindowPtr->WindowInstance = nullptr;

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL Resize(Window* WindowPtr, uint32_t Width, uint32_t Height)
        {
            int32_t operationSuccessful = 0;
            DWORD   errorCode           = 0;
     
            // Store the new requested size
            if (WindowPtr)
            {
                // Store the new Width and Height of the surface
                WindowPtr->ClientWidth  = Width;
                WindowPtr->ClientHeight = Height;

                // Create a RECT to define size of Window
                WindowPtr->ClientWindowRect = { 0, 0, static_cast<long>(Width), static_cast<long>(Height) };

                // Set Attributes for RECT
                if (!AdjustWindowRectEx(&WindowPtr->ClientWindowRect, WindowPtr->WindowStyle, false, WindowPtr->ExtendedWindowStyle))
                {
                    // TODO - Add error to log file
                    errorCode = GetLastError();
                }

                // Redraw window
                if (!RedrawWindow(WindowPtr->WindowHandle, &WindowPtr->ClientWindowRect, nullptr, RDW_INVALIDATE))
                {
                    // TODO - Add error to log file
                    errorCode = GetLastError();
                }
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL EnterFullscreen(Window* WindowPtr)
        {
            int32_t operationSuccessful = 0;
            DWORD   errorCode = 0;

            if (WindowPtr)
            {
                // Clear any window style since we are going fullscreen mode
                SetWindowLongPtr(WindowPtr->WindowHandle, GWL_STYLE,   0x00);
                SetWindowLongPtr(WindowPtr->WindowHandle, GWL_EXSTYLE, 0x00);

                // Set new window position
                if (!SetWindowPos(WindowPtr->WindowHandle,
                    nullptr,
                    WindowPtr->MonitorInfo.MonitorRect.left,
                    WindowPtr->MonitorInfo.MonitorRect.top,
                    WindowPtr->MonitorInfo.MonitorRect.right - WindowPtr->MonitorInfo.MonitorRect.left,
                    WindowPtr->MonitorInfo.MonitorRect.bottom - WindowPtr->MonitorInfo.MonitorRect.top,
                    SWP_NOZORDER | SWP_FRAMECHANGED))
                {
                    // TODO - Add error to log file
                    errorCode = GetLastError();
                }
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL ExitFullscreen(Window* WindowPtr)
        {
            int32_t operationSuccessful = 0;
            DWORD returnCode = 0;

            if (WindowPtr)
            {
                // Restore to previous style of the window
                SetWindowLongPtr(WindowPtr->WindowHandle, GWL_STYLE, WindowPtr->WindowStyle);
                SetWindowLongPtr(WindowPtr->WindowHandle, GWL_EXSTYLE, WindowPtr->ExtendedWindowStyle);

                // Set new window position based on stored RECT
                if (!SetWindowPos(WindowPtr->WindowHandle,
                    nullptr,
                    WindowPtr->ClientWindowRect.left,
                    WindowPtr->ClientWindowRect.top,
                    WindowPtr->ClientWindowRect.right - WindowPtr->ClientWindowRect.left,
                    WindowPtr->ClientWindowRect.bottom - WindowPtr->ClientWindowRect.top,
                    SWP_NOZORDER | SWP_FRAMECHANGED))
                {
                    returnCode = GetLastError();
                }

                // Activate window after updating style
                if (!ShowWindow(WindowPtr->WindowHandle, SW_SHOW))
                {
                    returnCode = GetLastError();
                }
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL IsWindowClosing(Window* WindowPtr)
        {
            int32_t windowClosing = 1;

            MSG currentMessage = { 0 };

            while (WM_QUIT != currentMessage.message)
            {
                if (GetMessage(&currentMessage, 0, 0, 0) > 0)
                {
                    TranslateMessage(&currentMessage);
                    DispatchMessage(&currentMessage);
                }
            }

            return windowClosing;
        }

        FR_API int32_t FR_CALL SetWindowTitle(Window* WindowPtr, const char* Title)
        {
            int32_t operationSuccessful = 0;

            // Create wide string because unicode requires a wstring
            std::wstring wWindowText;

            // Convert regular string to wstring
            for (size_t i = 0; i < strlen(Title); i++)
            {
                wWindowText += Title[i];
            }

            if (SetWindowText(WindowPtr->WindowHandle, wWindowText.c_str()))
            {
                operationSuccessful = 1;
            }
            else
            {
                // TODO: Add logging capabilities for each error message
                DWORD errorCode = GetLastError();
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL SetWindowIcon(Window* WindowPtr, const char* IconPath)
        {
            int32_t operationSuccessful = 0;

            // Create wide string because unicode requires a wstring
            std::wstring wIconPath;

            // Convert regular string to wstring
            for (size_t i = 0; i < strlen(IconPath); i++)
            {
                wIconPath += IconPath[i];
            }

            if (IconPath)
            {
                // Create and load the icon
                HICON newIcon = (HICON)LoadImage(NULL,
                    wIconPath.c_str(),
                    IMAGE_ICON,
                    0,
                    0,
                    LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);

                // Send a message to window to update the icon
                SendMessage(WindowPtr->WindowHandle, WM_SETICON, ICON_BIG, (LPARAM)newIcon);

                operationSuccessful = 1;
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL SetWindowStyle(Window* WindowPtr, int32_t WindowStyle)
        {
            int32_t operationSuccessful = 0;

            if (WindowPtr)
            { 
                if (SetWindowLongPtr(WindowPtr->WindowHandle, GWL_STYLE, WindowStyle))
                {
                    WindowPtr->WindowStyle = WindowStyle;
                    UpdateWindow(WindowPtr->WindowHandle);
                    ShowWindow(WindowPtr->WindowHandle, SW_SHOW);
                    operationSuccessful = 1;
                }
                else
                {
                    DWORD errorCode = GetLastError();
                }
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL SetWindowStyleExtended(Window* WindowPtr, int32_t WindowStyleExtended)
        {
            int32_t operationSuccessful = 0;

            if (WindowPtr)
            {
                if (SetWindowLongPtr(WindowPtr->WindowHandle, GWL_EXSTYLE, WindowStyleExtended))
                {
                    WindowPtr->ExtendedWindowStyle = WindowStyleExtended;
                    UpdateWindow(WindowPtr->WindowHandle);
                    ShowWindow(WindowPtr->WindowHandle, SW_SHOW);
                    operationSuccessful = 1;
                }
                else
                {
                    DWORD errorCode = GetLastError();
                }
            }

            return operationSuccessful;
        }

        FR_API int32_t FR_CALL SetWindowCursor(Window* WindowPtr, LPWSTR cursorSelection, const char *CursorPath)
        {
            SetCursor(LoadCursor(WindowPtr->WindowInstance, cursorSelection));

            return 0;
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

LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Grab window object pointer
    ForerunnerEngine::ForerunnerWindow::Window* thisWindowPtr = reinterpret_cast<ForerunnerEngine::ForerunnerWindow::Window*>(GetWindowLongPtr(handle, GWLP_USERDATA));

    switch (message)
    {
        case WM_NCCREATE:
        {
            // Get this pointer for the class to use
            thisWindowPtr = static_cast<ForerunnerEngine::ForerunnerWindow::Window*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

            /// Reset all errors
            SetLastError(0);

            if (!SetWindowLongPtr(handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(thisWindowPtr)))
            {
                if (GetLastError() != 0)
                {
                    return FALSE;
                }
            }

            return TRUE;
        }

        // Resolution change or another monitor was added
        case WM_DISPLAYCHANGE:
            return 0;

        // Check if joystick or device as added or remove
        case WM_DEVICECHANGE:
            return 0;

        case WM_MOUSEACTIVATE:
            SetFocus(handle);
            return 0;

        case WM_ACTIVATE:
            SetFocus(handle);
            return 0;

        case WM_CAPTURECHANGED:
            return 0;

        case WM_SETFOCUS:
            return 0;

        case WM_KILLFOCUS:
            return 0;

        case WM_DROPFILES:
        {
            HDROP handleDropFile = (HDROP)wParam;
            POINT mousePoint;

            // Get number of drag and drop files
            uint32_t fileCount = DragQueryFile(handleDropFile, 0xffffffff, NULL, 0);

            // Move the mouse to the position of the drop
            DragQueryPoint(handleDropFile, &mousePoint);

            for (uint32_t i = 0; i < fileCount; i++)
            {
                // Get length of file name
                uint32_t length = DragQueryFileW(handleDropFile, i, NULL, 0);

                // Get file path
                WCHAR filePath[512];

                // Store file name
                DragQueryFileW(handleDropFile, i, (LPWSTR)filePath, length + 1);
            }

            DragFinish(handleDropFile);

            return 0;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }

        case WM_ERASEBKGND:
        {
            return 0;
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            ::BeginPaint(handle, &ps);
            ::EndPaint(handle, &ps);
            return 0;
        }

        // Someone is resizing window
        case WM_SIZING:
        {
            return 0;
        }

        case WM_ENTERSIZEMOVE:
        {
            return 0;
        }

        case WM_EXITSIZEMOVE:
        {
            return 0;
        }

        /// LOWORD(lParam) = Width, HIWORD(lParam) = Height
        case WM_SIZE:
        {
            /// Check whether minimized or maximumized window
            switch (wParam)
            {
                case SIZE_MAXIMIZED:
                {
                    Resize(thisWindowPtr, LOWORD(lParam), HIWORD(lParam));
                    return 0;
                }

                case SIZE_MINIMIZED:
                {
                    return 0;
                }

                case SIZE_RESTORED:
                {
                    Resize(thisWindowPtr, LOWORD(lParam), HIWORD(lParam));
                    return 0;
                }

                case WM_ERASEBKGND:
                {
                    return TRUE;
                }

                default:
                    return 0;
            }
        }

        case WM_GETMINMAXINFO:
        {
            return 0;
        }

        case WM_LBUTTONUP:
        {
            auto mouseXCoordinate = GET_X_LPARAM(lParam);
            auto mouseYCoordinate = GET_Y_LPARAM(lParam);
            return 0;
        }

        case WM_LBUTTONDOWN:
        {
            auto mouseXCoordinate = GET_X_LPARAM(lParam);
            auto mouseYCoordinate = GET_Y_LPARAM(lParam);
            return 0;
        }

        case WM_MBUTTONUP:
        {
            auto mouseXCoordinate = GET_X_LPARAM(lParam);
            auto mouseYCoordinate = GET_Y_LPARAM(lParam);
            return 0;
        }

        case WM_MBUTTONDOWN:
        {
            auto mouseXCoordinate = GET_X_LPARAM(lParam);
            auto mouseYCoordinate = GET_Y_LPARAM(lParam);
            return 0;
        }

        case WM_RBUTTONUP:
        {
            auto mouseXCoordinate = GET_X_LPARAM(lParam);
            auto mouseYCoordinate = GET_Y_LPARAM(lParam);
            return 0;
        }

        case WM_RBUTTONDOWN:
        {
            auto mouseXCoordinate = GET_X_LPARAM(lParam);
            auto mouseYCoordinate = GET_Y_LPARAM(lParam);
            return 0;
        }

        case WM_MOUSEMOVE:
        {
            auto mouseXCoordinate = GET_X_LPARAM(lParam);
            auto mouseYCoordinate = GET_Y_LPARAM(lParam);
            return 0;
        }

        case WM_MOUSEWHEEL:
        {
            auto mouseMiddleXCoordinate = (GET_X_LPARAM(lParam));
            auto mouseMiddleYCoordinate = GET_WHEEL_DELTA_WPARAM(wParam);
            return 0;
        }

        default:
            return DefWindowProc(handle, message, wParam, lParam);
    }
}
