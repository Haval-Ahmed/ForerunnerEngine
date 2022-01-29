###########################################################################
### @File:
###     CMakeLists.txt
### @Notes:
###     Renderer Management CMake File
### @Copyright:
###		All rights reserved Haval Ahmed
###########################################################################

###########################################################################
### Define the project
###########################################################################
project(FRCamera LANGUAGES C CXX)

set (CAMERA_FILES
    Camera.h 
    Camera.cpp
    FreeMovementCamera.h
    FreeMovementCamera.cpp
)

# add the library
add_library (FRCamera SHARED ${CAMERA_FILES})

# Include Directories for Renderer
target_include_directories(FRCamera 
    PUBLIC 
        "${CMAKE_CURRENT_LIST_DIR}/"
        "${CMAKE_CURRENT_LIST_DIR}/..")

# Link libraries
target_link_libraries(FRCamera PUBLIC glm::glm)

# Define source grouping
source_group("Cameras" FILES ${CAMERA_FILES})

