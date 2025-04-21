project(hello_world)

add_executable(hello_world
    hello_world.cpp
)

target_link_libraries(hello_world
    xrbds
    glm::glm
)

# Project specific settings
set(TITLE       "Hello World")
set(PUBLISHER   "Built with xrbDS")
set(DEVELOPER   "Xarblanca")

nds_create_rom(
    hello_world
    NAME        ${TITLE}
    SUBTITLE1   ${PUBLISHER}
    SUBTITLE2   ${DEVELOPER}
)