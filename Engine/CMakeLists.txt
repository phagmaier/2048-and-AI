cmake_minimum_required(VERSION 3.30)  # Updated CMake version for modern features
project(Project)

# Set C++ standard to 20 and enforce it
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable maximum optimization for different build types
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# Add compiler optimization flags
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto -DNDEBUG" CACHE STRING "Release mode flags" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g" CACHE STRING "Debug mode flags" FORCE)

# Sources
set(SOURCES
  src/game.cpp
  src/main.cpp
  src/nn.cpp
  src/value.cpp
  src/myFunctions.cpp
  
)

# Add the executable
add_executable(runme ${SOURCES})

# Link time optimization (LTO)
set_property(TARGET runme PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
