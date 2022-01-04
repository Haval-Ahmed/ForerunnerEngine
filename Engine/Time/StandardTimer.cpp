//////////////////////////////////////////////////////////////////////////
/// @File:
///     StandardTimer.cpp
/// @Notes:
///     C++11 Implementation of high resolution timing
/// @Author:
///     Haval Ahmed
/// @Copyright:
///		All rights reserved Haval Ahmed
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <ratio>

//////////////////////////////////////////////////////////////////////////
/// User Defined Library Files
//////////////////////////////////////////////////////////////////////////
#include "StandardTimer.h"

namespace ForerunnerEngine
{
    StandardTimer::StandardTimer()
        : isApplicationPaused(false)
        , initialTime(std::chrono::high_resolution_clock::now())
        , currentTime(std::chrono::high_resolution_clock::now())
        , previousTime(std::chrono::high_resolution_clock::now())
        , pausedAtTime(std::chrono::high_resolution_clock::now())
    {
        
    }

    double StandardTimer::getTimeInSeconds(void)
    {
       return std::chrono::duration<double>(currentTime - initialTime).count();
    }

    double StandardTimer::getTimeInMiliseconds(void)
    {
        return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - initialTime)).count();
    }

    double StandardTimer::getTimeInMicroseconds(void)
    {
        return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - initialTime)).count();
    }

    double StandardTimer::getTimeInNanoseconds(void)
    {
        return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - initialTime)).count();
    }

    double StandardTimer::getDeltaTimeInSeconds(void)
    {
        return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::seconds>(deltaTime)).count();
    }

    double StandardTimer::getDeltaTimeInMiliseconds(void)
    {
        return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime)).count();
    }

    double StandardTimer::getDeltaTimeInMicroseconds(void)
    {
        return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::microseconds>(deltaTime)).count();
    }

    double StandardTimer::getDeltaTimeInNanoseconds(void)
    {
        return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime)).count();
    }

    double StandardTimer::getTotalTimeElapsedInSeconds(void)
    {
        /// If application was paused, calculate the difference accounting the duration of time paused
        if (isApplicationPaused)
        {
            return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::seconds>((pausedAtTime - durationOfTimePaused) - initialTime)).count();
        }
        else
        {
            return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::seconds>(currentTime - pausedAtTime) - std::chrono::time_point_cast<std::chrono::seconds>(initialTime).time_since_epoch()).count();
        }
    }

    double StandardTimer::getTotalTimeElapsedInMiliseconds(void)
    {
        /// If application was paused, calculate the difference accounting the duration of time paused
        if (isApplicationPaused)
        {
            return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>((pausedAtTime - durationOfTimePaused) - initialTime)).count();
        }
        else
        {
            return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - pausedAtTime) - std::chrono::time_point_cast<std::chrono::milliseconds>(initialTime).time_since_epoch()).count();
        }
    }

    double StandardTimer::getTotalTimeElapsedInMicroseconds(void)
    {
        /// If application was paused, calculate the difference accounting the duration of time paused
        if (isApplicationPaused)
        {
            return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::microseconds>((pausedAtTime - durationOfTimePaused) - initialTime)).count();
        }
        else
        {
            return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pausedAtTime) - std::chrono::time_point_cast<std::chrono::microseconds>(initialTime).time_since_epoch()).count();
        }
    }

    double StandardTimer::getTotalTimeElapsedInNanoseconds(void)
    {
        /// If application was paused, calculate the difference accounting the duration of time paused
        if (isApplicationPaused)
        {
            return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::nanoseconds>((pausedAtTime - durationOfTimePaused) - initialTime)).count();
        }
        else
        {
            return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - pausedAtTime) - std::chrono::time_point_cast<std::chrono::nanoseconds>(initialTime).time_since_epoch()).count();
        }
    }

    void StandardTimer::initalizeTimer(void)
    {
        /// Store Initial Time
        initialTime = std::chrono::high_resolution_clock::now();

        /// Check if we are restarting application from paused state
        if (isApplicationPaused)
        {
            /// Calculate the duration of time the application was paused/stopped
            durationOfTimePaused += initialTime - pausedAtTime;

            /// Reset previous time to new start time
            previousTime = initialTime;

            /// Reset Paused Time Counter
            pausedAtTime = std::chrono::high_resolution_clock::now();

            /// Set time stopped boolean to false
            isApplicationPaused = false;
        }
    }

    void StandardTimer::pauseTimer(void)
    {
        /// Check if application is already paused. 
        /// If so we don't want to do anything
        if (isApplicationPaused == false)
        {
            /// Set Paused Time to Current time
            pausedAtTime = std::chrono::high_resolution_clock::now();

            /// Set Application Paused to true
            isApplicationPaused = true;
        }
    }

    void StandardTimer::resetTimer(void)
    {
        /// Reset the value
        initialTime = std::chrono::high_resolution_clock::now();

        /// Reset previous time to new start time
        currentTime     = std::chrono::high_resolution_clock::now();
        previousTime    = initialTime;

        /// Reset timers
        pausedAtTime    = std::chrono::high_resolution_clock::now();
        deltaTime       = currentTime - previousTime;

        /// Set time stopped boolean to false
        isApplicationPaused = false;
    }

    void StandardTimer::tickTimer(void)
    {
        /// Check if application is paused
        if (isApplicationPaused)
        {
            /// Set Delta Time To Zero 
            deltaTime = std::chrono::high_resolution_clock::now() - std::chrono::high_resolution_clock::now();
        }
        else
        {
            /// Store current time
            currentTime = std::chrono::high_resolution_clock::now();

            /// Calculate the difference between current and last frame
            deltaTime = currentTime - previousTime;

            /// Store current time into previous time for next frame
            previousTime = currentTime;
        }
    }

}