###########################################################################
### @File:
###     CMakeLists.txt
### @Notes:
###     Time Management CMake File
### @Author:
###     Haval Ahmed
### @Copyright:
###     See attached license 
###     All rights reserved Haval Ahmed
###########################################################################

###########################################################################
### Define the project
###########################################################################
project(FRTime LANGUAGES C CXX)

###########################################################################
### Specify files for target
###########################################################################
set (TIME_FILES Timer.h BaseTimer.h StandardTimer.h StandardTimer.cpp)

###########################################################################
### Add platform specific code
###########################################################################
if (WIN32)
    set (TIME_FILES  ${TIME_FILES} WindowsTimer.h WindowsTimer.cpp)
endif()

###########################################################################
### Create target
###########################################################################
add_library (FRTime SHARED ${TIME_FILES})
 
