/// @file FRConfig.h
/// @brief Defines the API calling convention for the project
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

namespace ForerunnerEngine
{
    #if defined(FR_BUILD_AS_DLL)
        #define FR_API __declspec(dllexport)
    #elif defined(FR_CALL_AS_DLL)
        #define FR_API __declspec(dllimport)
    #else
        #define FR_API
    #endif

    #define FR_CALL __stdcall
}

#endif // FR_WINDOW_H