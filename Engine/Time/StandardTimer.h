//////////////////////////////////////////////////////////////////////////
/// @File:
///     StandardTimer.h
/// @Notes:
///     C++11 Standard Timing Class
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     See attached license 
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

#ifndef STANDARD_TIMER_H
#define STANDARD_TIMER_H

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <chrono>

//////////////////////////////////////////////////////////////////////////
/// Forerunner Libraries
//////////////////////////////////////////////////////////////////////////
#include "BaseTimer.h" 

namespace ForerunnerEngine
{
    class StandardTimer : public BaseTimer
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        /// Constructor
        //////////////////////////////////////////////////////////////////////////
        StandardTimer();

        //////////////////////////////////////////////////////////////////////////
        /// Virtual Destructor
        //////////////////////////////////////////////////////////////////////////
        virtual ~StandardTimer() {}

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

    private:

        //////////////////////////////////////////////////////////////////////////
        ///	Class Variables
        //////////////////////////////////////////////////////////////////////////
        bool                                            isApplicationPaused;
        std::chrono::duration<double>                   deltaTime;
        std::chrono::high_resolution_clock::time_point	initialTime;
        std::chrono::high_resolution_clock::time_point	currentTime;
        std::chrono::high_resolution_clock::time_point	previousTime;
        std::chrono::high_resolution_clock::time_point	pausedAtTime;
        std::chrono::duration<double>	                durationOfTimePaused;
    };
}

#endif /// TIMERWINDOWS_H