
# Create Buzzer library
add_library(buzzer)

#
target_sources(buzzer
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/audio.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/audio.hpp
    )

# Not sure what this does.
target_include_directories(buzzer
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )

target_link_libraries(buzzer portaudio_static)