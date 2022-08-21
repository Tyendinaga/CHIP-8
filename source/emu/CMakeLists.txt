
# Source Files
set(SRC_FILES
    private/cpu/cpu.cpp
    private/cpu/cpu.hpp
    private/audio/audio.cpp
    private/audio/audio.hpp
    private/display/display.cpp
    private/display/display.hpp
    private/emulator.cpp
    public/emulator.hpp
)

# Add Files from GLAD for OpenGL.
set (GLAD_FILES
    private/display/glad.c
    private/display/glad.h
    private/display/khrplatform.h
)

# Create Library
add_library(chip_emulator
    ${SRC_FILES}
    ${GLAD_FILES}
)

# Link Port Audio
target_link_libraries(chip_emulator
    PRIVATE
        portaudio_static
)

# Link GLFW3
target_link_libraries(chip_emulator
    PRIVATE
        glfw
)

target_include_directories(chip_emulator
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/public
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/private
)
