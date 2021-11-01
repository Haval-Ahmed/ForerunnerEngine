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

# Specify a minimum version
cmake_minimum_required(VERSION 3.20)

# Set the top level project name and version
project(ForerunnerEngine LANGUAGES CXX VERSION 0.1)

# Platform checks using check include files
include(CheckIncludeFiles)

# Check for SIMD support
CHECK_INCLUDE_FILES(arm_neon.h HAVE_ARM_NEON_SUPPORT)
CHECK_INCLUDE_FILES(immintrin.h HAVE_MMX_SUPPORT)
CHECK_INCLUDE_FILES(xmmintrin.h HAVE_SSE_SUPPORT)
CHECK_INCLUDE_FILES(emmintrin.h HAVE_SSE2_SUPPORT)
CHECK_INCLUDE_FILES(pmmintrin.h HAVE_SSE3_SUPPORT)

# Output the configured header file to our engine directory
configure_file(ForerunnerEngineConfig.h.in Engine/ForerunnerEngineConfig.h)

# Specify project options
option(ADDRESS_SANITIZER_ENABLED "Build this target with address sanitizer" ON)
option(BUILD_UNIT_TESTS "Build unit tests for this project" ON)

# Specify CTest for testing
include(CTest)

# Add subdirectories
add_subdirectory(Engine)
add_subdirectory(Editor)

if (BUILD_UNIT_TESTS)
    enable_testing()
    add_subdirectory(Test)
endif()
