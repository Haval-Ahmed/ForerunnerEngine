///////////////////////////////////////////////////////////////////////////////
//The MIT License (MIT)
//
//Copyright (c) 2016 Haval Ahmed
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.
///////////////////////////////////////////////////////////////////////////////

#ifndef FILE_PATHS_H
#define FILE_PATHS_H

//////////////////////////////////////////////////////////////////////////
// Standard Libraries
//////////////////////////////////////////////////////////////////////////
#include <filesystem>
#include <string>

namespace ForerunnerEngine
{
    //////////////////////////////////////////////////////////////////////////
    // Image Constants
    //////////////////////////////////////////////////////////////////////////
    std::string CORE_FILE_DIRECTORY         = std::filesystem::path(__FILE__).parent_path().string();
    std::string GAME_FILE_DIRECTORY         = CORE_FILE_DIRECTORY       + "/Game/";
    std::string IO_FILE_DIRECTORY           = CORE_FILE_DIRECTORY       + "/IO/";
    std::string MATH_FILE_DIRECTORY         = CORE_FILE_DIRECTORY       + "/Math/";
    std::string RENDERER_FILE_DIRECTORY     = CORE_FILE_DIRECTORY       + "/Renderer/";
    std::string SCENE_FILE_DIRECTORY        = CORE_FILE_DIRECTORY       + "/Scene/";
    std::string TIME_FILE_DIRECTORY         = CORE_FILE_DIRECTORY       + "/Time/";
    std::string WINDOW_FILE_DIRECTORY       = CORE_FILE_DIRECTORY       + "/Window/";
    std::string CAMERA_FILE_DIRECTORY       = RENDERER_FILE_DIRECTORY   + "Camera/";
    std::string LIGHTING_FILE_DIRECTORY     = RENDERER_FILE_DIRECTORY   + "Lighting/";
    std::string PRIMATIVES_FILE_DIRECTORY   = RENDERER_FILE_DIRECTORY   + "Primatives/";
    std::string SHADERS_FILE_DIRECTORY      = RENDERER_FILE_DIRECTORY   + "Shaders/";
    std::string GLSL_FILE_DIRECTORY         = SHADERS_FILE_DIRECTORY    + "GLSL/";
    std::string HLSL_FILE_DIRECTORY         = SHADERS_FILE_DIRECTORY    + "HLSL/";
}

#endif
