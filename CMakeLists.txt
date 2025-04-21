cmake_minimum_required(VERSION 3.15)

project(xrbDS)

include_directories(
  engine
  include/xrbds
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
  engine/*.cpp
)

add_library(xrbds
  ${SOURCES}
)

list(APPEND CMAKE_PREFIX_PATH "build")

find_package(glm REQUIRED)

target_link_libraries(xrbds
  PRIVATE glm::glm
  PRIVATE -lfilesystem
  PRIVATE -lfat
)

add_subdirectory(samples/hello_world)
