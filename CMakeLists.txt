# ##########################################
# GENERAL SETUP
#

cmake_minimum_required(VERSION 3.5.0)
project(chip8-emu)

# ##########################################
# External Packages
#

# Linux Specific Instructions
if (UNIX AND NOT APPLE)
    message(STATUS "Linux Build")

    # Get OpenGL
    find_package (OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS})

    # Get GLFW
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    include_directories(${GLFW_INCLUDE_DIRS})

    # Find X11
    find_package(X11 REQUIRED)

endif()

# Windows Instructions
if(WIN32)
    message(STATUS "Windows Build")

    # Disable GLFW Tests and Builds
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    # Get
    add_subdirectory(external/glfw-3.3.4)

endif()

# ##########################################
# Build Everything
#

add_subdirectory(source)