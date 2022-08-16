
# Get Source Files
set (SRC_FILES
    mainwindow.cpp
    mainwindow.h
)

# Get UI Files
set (UI_FILES
    mainwindow.ui
)

# Create Library
add_library(CHIP-8_UI ${SRC_FILES} ${UI_FILES})

# Bunch of Automatic QT Bullshit.
set_target_properties(CHIP-8_UI
    PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON
)

# AUTOMOC brings Windows.h to the sources so I just wanna clean that up a bit.
target_compile_definitions(CHIP-8_UI
    PRIVATE
        WIN32_LEAN_AND_MEAN
)

target_include_directories(CHIP-8_UI
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add in QT6
# Linking QT As Public exposes it to the rest of the
target_link_libraries(CHIP-8_UI
    PUBLIC
        Qt6::Widgets
)