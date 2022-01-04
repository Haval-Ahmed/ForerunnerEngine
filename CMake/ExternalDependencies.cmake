# Basic CMake file to define and require any packages needed for Forerunner Engine

# GLM is a required math library
find_package(glm CONFIG REQUIRED)

# We use glfw3 for window management
find_package(glfw3 CONFIG REQUIRED)

# IMGUI for editor
find_package(imgui CONFIG REQUIRED)

# target_link_libraries(main PRIVATE imgui::imgui)
# target_link_libraries(main PRIVATE glfw)