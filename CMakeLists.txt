# ##########################################
# GENERAL SETUP
#

cmake_minimum_required(VERSION 3.5.0)
project(chip8-emu)

# ##########################################
# External Packages
#

# Get OpenGL
find_package (OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Get GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

# Find X11
find_package(X11 REQUIRED)

# ##########################################
# Build Everything
#

add_subdirectory(source)