cmake_minimum_required(VERSION 3.16)

project(permute VERSION 1.1)

configure_file(config.h.in config.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(permute permute.cc)

target_include_directories(permute PUBLIC "${PROJECT_BINARY_DIR}")

install(TARGETS permute RUNTIME DESTINATION bin)
