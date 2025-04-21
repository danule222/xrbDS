project(hello_world)

add_executable(hello_world
    hello_world.cpp
)

target_link_libraries(hello_world
    xrbds
    glm::glm
)

# Project specific settings
set(TITLE       "Hello World")      # Title of the game
set(PUBLISHER   "Built with xrbDS") # Publisher of the game
set(DEVELOPER   "Xarblanca")        # Developer of the game
set(ASSETS      "assets")           # Path to the assets folder

nds_create_rom(
    hello_world
    NAME        ${TITLE}
    SUBTITLE1   ${PUBLISHER}
    SUBTITLE2   ${DEVELOPER}
    NITROFS     ${ASSETS}
    ICON        "${CMAKE_CURRENT_SOURCE_DIR}/icon.bmp"
)