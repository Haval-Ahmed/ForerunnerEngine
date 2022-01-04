/// @file BaseTimer.h
/// @brief BaseTimer Header File. Base class for all timing functions.
///     The goal of this library is to include a platform independent
///     timing library. Will use specific timing functions from specific
///     platform and will abstract to an easy to use layer.
/// @author Haval Ahmed

#ifndef BASETIMER_H
#define BASETIMER_H

namespace ForerunnerEngine
{
    class BaseTimer
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        /// Constructor
        //////////////////////////////////////////////////////////////////////////
        BaseTimer() {}

        //////////////////////////////////////////////////////////////////////////
        /// Virtual Destructor
        //////////////////////////////////////////////////////////////////////////
        virtual ~BaseTimer() {}

        //////////////////////////////////////////////////////////////////////////
        /// Getters
        //////////////////////////////////////////////////////////////////////////
        virtual double getTimeInSeconds(void)                   = 0;
        virtual double getTimeInMiliseconds(void)               = 0;
        virtual double getTimeInMicroseconds(void)              = 0;
        virtual double getTimeInNanoseconds(void)               = 0;
        virtual double getDeltaTimeInSeconds(void)              = 0;
        virtual double getDeltaTimeInMiliseconds(void)          = 0;
        virtual double getDeltaTimeInMicroseconds(void)         = 0;
        virtual double getDeltaTimeInNanoseconds(void)          = 0;
        virtual double getTotalTimeElapsedInSeconds(void)       = 0;
        virtual double getTotalTimeElapsedInMiliseconds(void)   = 0;
        virtual double getTotalTimeElapsedInMicroseconds(void)  = 0;
        virtual double getTotalTimeElapsedInNanoseconds(void)   = 0;

        //////////////////////////////////////////////////////////////////////////
        /// Utilities
        //////////////////////////////////////////////////////////////////////////
        virtual void initalizeTimer(void)   = 0;
        virtual void pauseTimer(void)       = 0;
        virtual void resetTimer(void)       = 0;
        virtual void tickTimer(void)        = 0;
    };
}

#endif /// BASETIMER_H