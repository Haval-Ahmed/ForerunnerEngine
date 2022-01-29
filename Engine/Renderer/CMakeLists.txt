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

project(FRRenderer LANGUAGES C CXX)

set (RENDERER_FILES 
    Renderer.h
    BaseRenderer.h 
    BaseRenderer.cpp
    OpenGLRenderer.h
    OpenGLRenderer.cpp
    OpenGLTexture.h
    OpenGLTexture.cpp
    Colors.h
)

set (SHADER_FILES
    Shaders/BaseShader.h
    Shaders/OpenGLShader.h
    Shaders/OpenGLShader.cpp
    Shaders/GLSLShaders.h
)

set (PRIMITIVE_FILES
    Primitives/PrimitiveData2D.h
    Primitives/PrimitiveData3D.h
    Primitives/Transform.h
    Primitives/Vertices.h
    Primitives/OpenGLPrimitive2D.h
    #Primitives/OpenGLPrimitive3D.h
    Primitives/OpenGLPrimitive2D.cpp
    #Primitives/OpenGLPrimitive3D.cpp
)

if (WIN32)
    # list (APPEND RENDERER_FILES D3D11Renderer.h D3D11Renderer.cpp)
    # list (APPEND SHADER_FILES Shaders/D3D11Shader.h Shaders/D3D11Shader.cpp)
    # list (APPEND PRIMATIVE_FILES Primatives/D3D11PrimativeManager.h Primatives/D3D11PrimativeManager.cpp)
endif()

# Create the target
add_library (FRRenderer STATIC ${RENDERER_FILES} ${SHADER_FILES} ${PRIMITIVE_FILES})

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

# Specify target options
target_compile_options(FRRenderer PRIVATE ${TargetCompileOptions})
target_compile_definitions(FRRenderer PUBLIC ${TargetCompileDefines})

# Include Directories for Renderer
target_include_directories(FRRenderer 
    PUBLIC 
        ./
        ./Lighting
        ./Primitives
        ./Shaders
        ./../Window
        ./../Config
        ./../../3rdParty/glad
)

# Target Link Libraries for Renderer
target_link_libraries(FRRenderer PUBLIC FRIO FRWindow glm::glm imgui::imgui)

# Define source grouping
source_group("Renderer"     FILES ${RENDERER_FILES})
source_group("Primitives"   FILES ${PRIMITIVE_FILES})
source_group("Shaders"      FILES ${SHADER_FILES})
