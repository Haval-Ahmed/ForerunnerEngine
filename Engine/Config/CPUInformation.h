/// @file FRCPUInformation.h
/// @brief CPU functions and checks to understand the CPU architecture available
/// @author Haval Ahmed (Haval-Ahmed)

#ifndef FR_CPU_INFORMATION_H
#define FR_CPU_INFORMATION_H

///////////////////////////////////////////////////////////////////////////////
/// Standard Libraries
///////////////////////////////////////////////////////////////////////////////
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
///////////////////////////////////////////////////////////////////////////////
#include "ProjectConfig.h"

namespace ForerunnerEngine
{
    constexpr int32_t MAX_PROCESSOR_NAME_SIZE = 128;

    struct FR_CPUInformation
    {
        uint8_t NumberOfCores;
        char ProcessorName[MAX_PROCESSOR_NAME_SIZE];
    };

    extern FR_API int32_t FR_CALL InitializeCPUInformation(FR_CPUInformation& CPUInfo);
    extern FR_API int32_t FR_CALL GetCPUCoreCount(void);
}

#endif // FR_WINDOW_H