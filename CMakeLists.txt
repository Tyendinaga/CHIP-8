# ##########################################
# GENERAL SETUP
#

cmake_minimum_required(VERSION 3.16)
project(CHIP-8)

# Print CMAKE Version
message(${CMAKE_VERSION})

# ##########################################
# External Packages
#

# Windows Instructions
if(WIN32)
    message(STATUS "Windows Build")

    # Disable GLFW Tests and Builds
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    # Build GLFW3
    add_subdirectory(external/glfw-3.3.4)

    # Build Port Audio
    add_subdirectory(external/portaudio-19.7.0)

    # Get QT Package.
    set(CMAKE_PREFIX_PATH "C:\\Qt\\6.3.1\\msvc2019_64\\lib\\cmake")
    find_package(Qt6 REQUIRED COMPONENTS Widgets)
    qt_standard_project_setup()

endif()

# ##########################################
# Build Everything
#

add_subdirectory(source)