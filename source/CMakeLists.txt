



set(SOURCES
    main.cpp
)

add_executable(CHIP-8
    ${SOURCES}
)

# Link in Gui Library
add_subdirectory(gui)
target_link_libraries(CHIP-8
    chip_gui
)

add_subdirectory(emu)
target_link_libraries(CHIP-8
    chip_emulator
)