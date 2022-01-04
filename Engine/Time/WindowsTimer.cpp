//////////////////////////////////////////////////////////////////////////
/// @File:
///     WindowsTimer.cpp
/// @Notes:
///     BaseTimer Header File. Base class for all timing functions.
///     The goal of this library is to include a platform independent
///     timing library. Will use specific timing functions from specific
///     platform and will abstract to an easy to use layer.
/// @Author:
///     Haval Ahmed
/// @Copyright:
///     See attached license 
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// User Defined Library Files
//////////////////////////////////////////////////////////////////////////
#include "WindowsTimer.h"

namespace ForerunnerEngine
{
    WindowsTimer::WindowsTimer() 
        : mIsApplicationPaused(false)
        , mClockFrequencySeconds(0.0)
        , mClockFrequencyMiliseconds(0.0)
        , mClockFrequencyMicroseconds(0.0)
        , mClockFrequencyNanoSeconds(0.0)
        , mDeltaTime(0)
        , mInitialTime(0)
        , mCurrentTime(0)
        , mPreviousTime(0)
        , mPausedAtTime(0)
        , mDurationOfTimePaused(0)
    {
        /// Retrieves the frequency of the performance counter. 
        /// The frequency of the performance counter is fixed at system boot and is consistent across all processors. 
        QueryPerformanceFrequency(&mPerformanceFrequency);

        /// Get clock frequency for seconds
        mClockFrequencySeconds         = (SECOND_TIME_FORMAT       / static_cast<double>(mPerformanceFrequency.QuadPart));
        mClockFrequencyMiliseconds     = (MILISECOND_TIME_FORMAT   / static_cast<double>(mPerformanceFrequency.QuadPart));
        mClockFrequencyMicroseconds    = (MICROSECOND_TIME_FORMAT  / static_cast<double>(mPerformanceFrequency.QuadPart));
        mClockFrequencyNanoSeconds     = (NANOSECOND_TIME_FORMAT   / static_cast<double>(mPerformanceFrequency.QuadPart));
    }

    double WindowsTimer::getTimeInSeconds(void)
    {
        return static_cast<double>((mCurrentTime - mInitialTime) * mClockFrequencySeconds);
    }

    double WindowsTimer::getTimeInMiliseconds(void)
    {
        return static_cast<double>((mCurrentTime - mInitialTime) * mClockFrequencySeconds);
    }

    double WindowsTimer::getTimeInMicroseconds(void)
    {
        return static_cast<double>((mCurrentTime - mInitialTime) * mClockFrequencyMicroseconds);
    }

    double WindowsTimer::getTimeInNanoseconds(void)
    {
        return static_cast<double>((mCurrentTime - mInitialTime) * mClockFrequencyNanoSeconds);
    }

    double WindowsTimer::getDeltaTimeInSeconds(void)
    {
        return static_cast<double>(mDeltaTime * mClockFrequencySeconds);
    }

    double WindowsTimer::getDeltaTimeInMiliseconds(void)
    {
        return static_cast<double>(mDeltaTime * mClockFrequencySeconds);
    }

    double WindowsTimer::getDeltaTimeInMicroseconds(void)
    {
        return static_cast<double>(mDeltaTime * mClockFrequencyMicroseconds);
    }

    double WindowsTimer::getDeltaTimeInNanoseconds(void)
    {
        return static_cast<double>(mDeltaTime * mClockFrequencyNanoSeconds);
    }

    double WindowsTimer::getTotalTimeElapsedInSeconds(void)
    {
        /// If application was paused, calculate the difference accounting the duration of time paused
        if (mIsApplicationPaused)
        {
            return static_cast<double>(((mPausedAtTime - mDurationOfTimePaused) - mInitialTime) * mClockFrequencySeconds);
        }
        else
        {
            return static_cast<double>(((mCurrentTime - mPreviousTime) - mInitialTime) * mClockFrequencySeconds);
        }
    }

    double WindowsTimer::getTotalTimeElapsedInMiliseconds(void)
    {
        /// If application was paused, calculate the difference accounting the duration of time paused
        if (mIsApplicationPaused)
        {
            return static_cast<double>(((mPausedAtTime - mDurationOfTimePaused) - mInitialTime) * mClockFrequencySeconds);
        }
        else
        {
            return static_cast<double>(((mCurrentTime - mPreviousTime) - mInitialTime) * mClockFrequencySeconds);
        }
    }

    double WindowsTimer::getTotalTimeElapsedInMicroseconds(void)
    {
        /// If application was paused, calculate the difference accounting the duration of time paused
        if (mIsApplicationPaused)
        {
            return static_cast<double>(((mPausedAtTime - mDurationOfTimePaused) - mInitialTime) * mClockFrequencyMicroseconds);
        }
        else
        {
            return static_cast<double>(((mCurrentTime - mPreviousTime) - mInitialTime) * mClockFrequencyMicroseconds);
        }
    }

    double WindowsTimer::getTotalTimeElapsedInNanoseconds(void)
    {
        /// If application was paused, calculate the difference accounting the duration of time paused
        if (mIsApplicationPaused)
        {
            return static_cast<double>(((mPausedAtTime - mDurationOfTimePaused) - mInitialTime) * mClockFrequencyNanoSeconds);
        }
        else
        {
            return static_cast<double>(((mCurrentTime - mPreviousTime) - mInitialTime) * mClockFrequencyNanoSeconds);
        }
    }

    void WindowsTimer::initalizeTimer(void)
    {
        /// Grab the initial time for the application
        /// QueryPerformanceCounter will give us the current time
        QueryPerformanceCounter(&mPerformanceCounter);

        /// Store Initial Time
        mInitialTime = mPerformanceCounter.QuadPart;

        /// Check if we are restarting application from paused state
        if (mIsApplicationPaused)
        {
            /// Calculate the duration of time the application was paused/stopped
            mDurationOfTimePaused += mInitialTime - mPausedAtTime;

            /// Reset previous time to new start time
            mPreviousTime = mInitialTime;

            /// Reset Paused Time Counter
            mPausedAtTime = 0;

            /// Set time stopped boolean to false
            mIsApplicationPaused = false;
        }
    }

    void WindowsTimer::pauseTimer(void)
    {
        /// Check if application is already paused. 
        /// If so we don't want to do anything
        if (mIsApplicationPaused == false)
        {
            QueryPerformanceCounter(&mPerformanceCounter);

            /// Set Paused Time to Current time
            mPausedAtTime = mPerformanceCounter.QuadPart;

            /// Set Application Paused to true
            mIsApplicationPaused = true;
        }
    }

    void WindowsTimer::resetTimer(void)
    {
        /// Grab new initial start time
        QueryPerformanceCounter(&mPerformanceCounter);

        /// Reset the value
        mInitialTime = mPerformanceCounter.QuadPart;

        /// Reset previous time to new start time
        mPreviousTime = mInitialTime;

        /// Reset timers
        mPausedAtTime   = 0;
        mDeltaTime      = 0;
        mCurrentTime    = 0;

        /// Set time stopped boolean to false
        mIsApplicationPaused = false;
    }

    void WindowsTimer::tickTimer(void)
    {
        /// Check if application is paused
        if (mIsApplicationPaused)
        {
            /// Set Delta Time To Zero 
            mDeltaTime = 0;
        }
        else
        {
            /// Get tick count
            QueryPerformanceCounter(&mPerformanceCounter);

            /// Store current time
            mCurrentTime = mPerformanceCounter.QuadPart;

            /// Calculate the difference between current and last frame
            /// NOTE FOR FUTURE. REMOVED DELTA NEGATIVE CHECK
            mDeltaTime = mCurrentTime - mPreviousTime;

            /// Store current time into previous time for next frame
            mPreviousTime = mCurrentTime;
        }
    }

}