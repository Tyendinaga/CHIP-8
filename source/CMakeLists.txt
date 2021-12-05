set(SOURCES main.cpp 
            cpu/chip8.cpp
            display/display.cpp
            display/glad.c
            audio/audio.cpp)

set (HEADERS cpu/chip8.hpp
            display/display.hpp
            display/glad.h
            display/khrplatform.h
            audio/audio.hpp)

add_executable(CHIP-8 ${SOURCES} ${HEADERS})

include_directories(cpu display)

# Link GLFW3 with the App
target_link_libraries(CHIP-8 glfw)

# Link PortAudio with the App
target_link_libraries(CHIP-8 portaudio_static)

#target_link_libraries(EmuC8 ${OPENGL_LIBRARIES})
#target_link_libraries(EmuC8 ${GLFW_STATIC_LIBRARIES})
#target_link_libraries(EmuC8 pthread)
#target_link_libraries(EmuC8 ${X11_LIBRARIES})