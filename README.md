## Introduction

This repository contains the source code for the Forerunner Engine. It is a custom 3D game engine written in C/C++. It is a sequel/fork based on my original Forerunner Engine (legacy). 

The overall goals for this project are learning and designing a game engine with ease of creation as the fore-front. This engine wasn't made to compete with the titan's but as a custom solution specifically to for learning purposes. 

## Development 

This repository will contain 3rd party dependencies as need and where it makes sense. In the previous iteration of the engine I decided to write everything myself with no external dependencies. I have realized while that is good for initial learning, is extremely time consuming and should not be the focus of this project. The focus of this project is to prototype as easily and quickly as possible. 

## Building 

I have tried to make this repository extremely easy to build. I would strongly recommend using vcpkg as I pull some necessary 3rd party dependencies such as glm (math) and glfw.

Example on how to generate the project files for Visual Studio. 

```bash
mkdir build 
cd build 
cmake -G "Visual Studio 17 2022" ..
```

## Dependencies 

Here are the dependencies, libraries, tools that were used or required to build the forerunner engine. 

Note:

For Windows you will need an MSVC compiler (I used MSVC 160 or V142). 

For Linux you will need an LLVM(Clang) compiler. I test with LLVM 11.0+. 

Name | Description | Required | Version |
| :-: | :-: | :-: | :-: |
CMake | Project Configuration | Yes | 3.20+
Visual Studio | C++ Compiler and IDE | Yes | Visual Studio 2022
LLVM | C++ Compiler | Yes | 11.0+
Doxygen | Documentation Generator | No | 1.9.2
vcpkg | Cross platform package manager | No | Latest

Name | Description | Required |
| :-: | :-: | :-: |
GLFW | Cross Platform Windowing Library | YES |
GLM | Cross Platform Math library | YES |

## License

The MIT License (MIT)

Copyright (c) 2016 Haval Ahmed

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
