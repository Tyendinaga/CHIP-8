# ##########################################
# GENERAL SETUP
#

cmake_minimum_required(VERSION 3.5.0)
project(chip8-emu)

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

endif()

# ##########################################
# Build Everything
#

add_subdirectory(source)