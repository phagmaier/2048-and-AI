cmake_minimum_required(VERSION 3.5)
project(Project)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES
src/game.cpp
src/main.cpp
src/nn.cpp
)
add_executable(runme ${SOURCES})
