//////////////////////////////////////////////////////////////////////////
/// @File:
///     WindowsTimer.h
/// @Notes:
///     Timing class for Windows(Win32) platforms
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     See attached license 
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

#ifndef WINDOWS_TIMER_H
#define WINDOWS_TIMER_H

//////////////////////////////////////////////////////////////////////////
// Standard Library
//////////////////////////////////////////////////////////////////////////
#include <cstdint>

//////////////////////////////////////////////////////////////////////////
/// Platform Specific Libraries 
//////////////////////////////////////////////////////////////////////////
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "BaseTimer.h" 

namespace ForerunnerEngine
{
    class WindowsTimer : public BaseTimer
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        /// Constructor
        //////////////////////////////////////////////////////////////////////////
        WindowsTimer();

        //////////////////////////////////////////////////////////////////////////
        /// Virtual Destructor
        //////////////////////////////////////////////////////////////////////////
        virtual ~WindowsTimer() {}

        //////////////////////////////////////////////////////////////////////////
        /// Getters
        //////////////////////////////////////////////////////////////////////////
        virtual double getTimeInSeconds(void);
        virtual double getTimeInMiliseconds(void);
        virtual double getTimeInMicroseconds(void);
        virtual double getTimeInNanoseconds(void);
        virtual double getDeltaTimeInSeconds(void);
        virtual double getDeltaTimeInMiliseconds(void);
        virtual double getDeltaTimeInMicroseconds(void);
        virtual double getDeltaTimeInNanoseconds(void);
        virtual double getTotalTimeElapsedInSeconds(void);
        virtual double getTotalTimeElapsedInMiliseconds(void);
        virtual double getTotalTimeElapsedInMicroseconds(void);
        virtual double getTotalTimeElapsedInNanoseconds(void);

        //////////////////////////////////////////////////////////////////////////
        /// Utilities
        //////////////////////////////////////////////////////////////////////////
        virtual void initalizeTimer(void);
        virtual void pauseTimer(void);
        virtual void resetTimer(void);
        virtual void tickTimer(void);

    protected:

        //////////////////////////////////////////////////////////////////////////
        ///	Class Constants - Scope level only to class
        //////////////////////////////////////////////////////////////////////////
        const double SECOND_TIME_FORMAT         = 1.0;
        const double MILISECOND_TIME_FORMAT     = 1000.0;
        const double MICROSECOND_TIME_FORMAT    = 1000000.0;
        const double NANOSECOND_TIME_FORMAT     = 1000000000.0;

        //////////////////////////////////////////////////////////////////////////
        ///	Class Variables
        //////////////////////////////////////////////////////////////////////////
        bool        mIsApplicationPaused;
        double      mClockFrequencySeconds;
        double      mClockFrequencyMiliseconds;
        double      mClockFrequencyMicroseconds;
        double      mClockFrequencyNanoSeconds;
        uint64_t    mDeltaTime;
        uint64_t    mInitialTime;
        uint64_t    mCurrentTime;
        uint64_t    mPreviousTime;
        uint64_t    mPausedAtTime;
        uint64_t    mDurationOfTimePaused;

        //////////////////////////////////////////////////////////////////////////
        ///	WIN32 Variables
        //////////////////////////////////////////////////////////////////////////
        LARGE_INTEGER mPerformanceCounter   = { 0 };    // Used for QueryPerformanceCounter
        LARGE_INTEGER mPerformanceFrequency = { 0 };    // Used for QueryPerformanceFrequency
    };
}

#endif /// TIMERWINDOWS_H