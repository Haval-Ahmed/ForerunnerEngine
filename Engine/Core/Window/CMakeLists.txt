# The MIT License (MIT)
# 
# Copyright (c) 2016 Haval Ahmed
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

project(FRWindowLibrary C CXX)

if (UNIX)
    find_package(X11 REQUIRED)
    message(STATUS "X11_FOUND       = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES   = ${X11_LIBRARIES}")
endif()

# Specify common files for target
set (CommonWindowFiles Window.h)

# Platform specific files
if (WIN32)
    list (APPEND CommonWindowFiles Win32Window.h Win32Window.cpp)
else()
    list (APPEND CommonWindowFiles X11Window.h X11Window.cpp ../../../3rdParty/glad/glad_glx.h ../../../3rdParty/glad/glad_glx.c)
endif()

# Create the target
add_library (FRWindowLibrary SHARED ${CommonWindowFiles})

# Specify includes for target
set (TargetIncludeDirs ./ ../ ../../Config ../../../3rdParty/)

if (UNIX)
    list(APPEND TargetIncludeDirs ${X11_INCLUDE_DIR})
endif()

# Specify compile options for definition
set (TargetCompileDefines)
set (TargetCompileOptions)

if (UNIX)
    list(APPEND TargetCompileDefines LINUX)
endif()

if(MSVC)
    list(APPEND TargetCompileOptions /Zi /W4)
else()
    list(APPEND TargetCompileOptions)
endif()

if (WIN32)
    list(APPEND TargetLinkLibs Shore)
elseif(UNIX)
    list(APPEND TargetLinkLibs ${CMAKE_DL_LIBS} pthread ${X11_LIBRARIES})
endif()

# Define the target configuration in terms of compile options, directories, definitions, etc..
target_compile_options(FRWindowLibrary PRIVATE ${TargetCompileOptions})
target_compile_definitions(FRWindowLibrary PUBLIC ${TargetCompileDefines})
target_include_directories(FRWindowLibrary PUBLIC ${TargetIncludeDirs})
target_link_libraries(FRWindowLibrary PUBLIC ${TargetLinkLibs})