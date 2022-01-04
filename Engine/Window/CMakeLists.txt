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

project(FRWindow C CXX)

if (UNIX)
    find_package(X11 REQUIRED)
    message(STATUS "X11_FOUND       = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES   = ${X11_LIBRARIES}")
endif()

# Specify common files for target
set (CommonWindowFiles Window.h ${PROJECT_SOURCE_DIR}/../../3rdParty/glad/glad.c)

# Create the target
add_library (FRWindow INTERFACE)

# Specify includes for target
set (TargetIncludeDirs ./ ../Config ../../3rdParty/)

# Specify compile options for definition
set (TargetLinkLibs glfw)

if (WIN32)
    list(APPEND TargetLinkLibs Shcore)
elseif(UNIX)
    list(APPEND TargetLinkLibs ${CMAKE_DL_LIBS} pthread)
endif()

# Define the target configuration in terms of compile options, directories, definitions, etc..
target_include_directories(FRWindow INTERFACE ${TargetIncludeDirs})
target_link_libraries(FRWindow INTERFACE ${TargetLinkLibs})
target_sources(FRWindow INTERFACE ${CommonWindowFiles})