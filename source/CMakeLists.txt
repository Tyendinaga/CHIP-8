



set(SOURCES main.cpp
    cpu/chip8.cpp
    display/display.cpp
    display/glad.c
    )

set (HEADERS cpu/chip8.hpp
    display/display.hpp
    display/glad.h
    display/khrplatform.h
    )

add_executable(CHIP-8 ${SOURCES} ${HEADERS})

include_directories(cpu display)

# Link in Audio Library
add_subdirectory(audio)
target_link_libraries(CHIP-8
    buzzer
)

# Link in Gui Library
add_subdirectory(gui)
target_link_libraries(CHIP-8
    CHIP-8_UI
)

# Link GLFW3 with the App
target_link_libraries(CHIP-8
    glfw
)

# Link PortAudio with the App
target_link_libraries(CHIP-8
    portaudio_static
)