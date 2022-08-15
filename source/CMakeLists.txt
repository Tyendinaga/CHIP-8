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
target_link_libraries(CHIP-8 buzzer)

# Link GLFW3 with the App
target_link_libraries(CHIP-8 glfw)

# Link PortAudio with the App
target_link_libraries(CHIP-8 portaudio_static)

# Link QT Into the App
target_link_libraries(CHIP-8 Qt6::Widgets)