/// @File:
///     FRTime.h
/// @Details:
///     The goal of this library is to include a platform independent
///     timing library. Will use specific timing functions from specific
///     platform and will abstract to an easy to use layer.
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     All rights reserved Haval Ahmed

#ifndef TIMER_H
#define TIMER_H

#if defined(WIN32)

    #include "WindowsTimer.h" 
    typedef ForerunnerEngine::WindowsTimer Timer;

#elif defined(LINUX)

    #include "StandardTimer.h"
    typedef ForerunnerEngine::StandardTimer Timer;

#endif 

#endif /// TIMER_H
