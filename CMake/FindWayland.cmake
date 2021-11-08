# Basic FindWayland.cmake module to find Wayland Client and Server include directories and libraries
# These module will define the following variables if sucessful
# WAYLAND_FOUND
# WAYLAND_CLIENT_INCLUDE_DIR
# WAYLAND_CLIENT_LIBRARY
# WAYLAND_SERVER_INCLUDE_DIR
# WAYLAND_SERVER_LIBRARY
# WAYLAND_EGL_INCLUDE_DIR
# WAYLAND_EGL_LIBRARY

include(FindPackageHandleStandardArgs)

# Find client and server includes
find_path(WAYLAND_CLIENT_INCLUDE_DIR  NAMES wayland-client.h)
find_path(WAYLAND_SERVER_INCLUDE_DIR  NAMES wayland-server.h)
find_path(WAYLAND_EGL_INCLUDE_DIR     NAMES wayland-egl.h)

# Find client and server libraries
find_library(WAYLAND_CLIENT_LIBRARY NAMES wayland-client libwayland-client)
find_library(WAYLAND_SERVER_LIBRARY NAMES wayland-server libwayland-server)
find_library(WAYLAND_EGL_LIBRARY    NAMES wayland-egl libwayland-egl)

# Check if we have found the client locations
if(WAYLAND_CLIENT_INCLUDE_DIR AND WAYLAND_CLIENT_LIBRARY)

    # Per cmake documentation on usage of unknown
    # It allows the path to an imported library (often found using the find_library() command) 
    # to be used without having to know what type of library it is. 
    add_library(Wayland::Client UNKNOWN IMPORTED)

    set_target_properties(Wayland::Client   PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES       "${WAYLAND_CLIENT_INCLUDE_DIR}"
        IMPORTED_LINK_INTERFACE_LANGUAGES   "C"
        IMPORTED_LOCATION                   "${WAYLAND_CLIENT_LIBRARY}"
    )
endif()

# Check if we have found the server locations
if(WAYLAND_SERVER_INCLUDE_DIR AND WAYLAND_SERVER_LIBRARY)

    # Create server alias
    add_library(Wayland::Server UNKNOWN IMPORTED)

    set_target_properties(Wayland::Server   PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES       "${WAYLAND_SERVER_INCLUDE_DIR}"
        IMPORTED_LINK_INTERFACE_LANGUAGES   "C"
        IMPORTED_LOCATION                   "${WAYLAND_SERVER_LIBRARY}"
    )
endif()

# Check if we have found the egl locations
if(WAYLAND_EGL_INCLUDE_DIR AND WAYLAND_EGL_LIBRARY)

    # Create server alias
    add_library(Wayland::EGL UNKNOWN IMPORTED)

    set_target_properties(Wayland::EGL      PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES       "${WAYLAND_CLIENT_INCLUDE_DIR}"
        IMPORTED_LINK_INTERFACE_LANGUAGES   "C"
        IMPORTED_LOCATION                   "${WAYLAND_EGL_LIBRARY}"
    )
endif()

set(_WAYLAND_REQUIRED_VARS 
    WAYLAND_CLIENT_INCLUDE_DIR 
    WAYLAND_SERVER_INCLUDE_DIR 
    WAYLAND_EGL_INCLUDE_DIR
    WAYLAND_CLIENT_LIBRARY
    WAYLAND_SERVER_LIBRARY
    WAYLAND_EGL_LIBRARY
)

find_package_handle_standard_args(WAYLAND
    REQUIRED_VARS 
    _WAYLAND_REQUIRED_VARS 
)

mark_as_advanced(
    WAYLAND_FOUND
    WAYLAND_CLIENT_INCLUDE_DIR
    WAYLAND_CLIENT_LIBRARY
    WAYLAND_SERVER_INCLUDE_DIR
    WAYLAND_SERVER_LIBRARY
    WAYLAND_EGL_INCLUDE_DIR
    WAYLAND_EGL_LIBRARY
)