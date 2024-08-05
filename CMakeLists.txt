cmake_minimum_required(VERSION 3.20)

# Set the project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the Raylib package using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

# Define sources
set(SOURCES
    brain.cpp
    main.cpp
)

# Specify your executable
add_executable(runme ${SOURCES})

# Include directories
target_include_directories(runme PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${RAYLIB_INCLUDE_DIRS}
)

# Link the libraries
target_link_libraries(runme PRIVATE ${RAYLIB_LIBRARIES})

# Set the build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set compiler options for different build types
target_compile_options(runme PRIVATE
    $<$<CONFIG:Debug>:-g>                          # Debugging symbols
    $<$<CONFIG:Release>:-O3 -DNDEBUG>              # Optimization level 3 and disable assertions
    $<$<CONFIG:RelWithDebInfo>:-O2 -g>             # Optimization level 2 with debugging symbols
    $<$<CONFIG:MinSizeRel>:-Os -DNDEBUG>           # Optimization for size and disable assertions
)

