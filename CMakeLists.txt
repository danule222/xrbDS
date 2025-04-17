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

add_subdirectory(samples/hello_world)
