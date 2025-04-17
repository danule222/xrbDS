cmake_minimum_required(VERSION 3.15)

project(xrbDS)

include_directories(
  include/xrbds
)

add_library(xrbds
  engine/core/engine.cpp
)

add_subdirectory(samples/hello_world)
