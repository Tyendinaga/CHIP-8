
# Get Source Files
set (SRC_FILES
    mainwindow.cpp
    mainwindow.h
)

# Get UI Files
set (UI_FILES
    mainwindow.ui
)

# Get Resources
set (RES_FILES
    resources.qrc
)

# Create Library
add_library(chip_gui
    ${SRC_FILES}
    ${UI_FILES}
    ${RES_FILES}
)

# Bunch of Automatic QT Bullshit.
set_target_properties(chip_gui
    PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON
)

# AUTOMOC brings Windows.h to the sources so I just wanna clean that up a bit.
target_compile_definitions(chip_gui
    PRIVATE
        WIN32_LEAN_AND_MEAN
)

target_include_directories(chip_gui
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Link GLFW3
target_link_libraries(chip_gui
    PRIVATE
        glfw
)

# Add in QT6
# Linking QT As Public exposes it to the rest of the
target_link_libraries(chip_gui
    PUBLIC
        Qt6::Widgets
)

# Link Chip Emulator
target_link_libraries(chip_gui
    PRIVATE
        chip_emulator
)