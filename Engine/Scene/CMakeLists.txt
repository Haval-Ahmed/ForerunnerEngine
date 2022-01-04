###########################################################################
### @File:
###     CMakeLists.txt
### @Notes:
###     Testing CMake File
### @Author:
###     Haval Ahmed
### @Copyright:
###     See attached license 
###		All rights reserved Haval Ahmed
###########################################################################

###########################################################################
### Define Project
###########################################################################
project(FRScene)

###########################################################################
### Specify project files
###########################################################################
set (SCENE_FILES
    BaseScene.h
    OpenGLScene.h
    OpenGLScene.cpp
)

###########################################################################
### Define the target
###########################################################################
add_library (FRScene STATIC ${SCENE_FILES})

###########################################################################
# Configure Target
###########################################################################
target_include_directories(FRScene 
    PUBLIC 
        "${CMAKE_CURRENT_LIST_DIR}/"
        "${CMAKE_CURRENT_LIST_DIR}/../IO"
        "${CMAKE_CURRENT_LIST_DIR}/../Math"
        "${CMAKE_CURRENT_LIST_DIR}/../Window"
        "${CMAKE_CURRENT_LIST_DIR}/../Renderer"
        "${CMAKE_CURRENT_LIST_DIR}/../Renderer/Primatives"
        "${CMAKE_CURRENT_LIST_DIR}/../Renderer/Shaders"
        "${CMAKE_CURRENT_LIST_DIR}/../Camera"
        "${CMAKE_CURRENT_LIST_DIR}/../../3rdParty/glad/include")

add_dependencies(FRScene 
    FRWindow 
    FRTime 
    FRMath
    FRRenderer
    FRIO
    FRCamera
)



