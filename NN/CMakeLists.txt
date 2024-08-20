cmake_minimum_required(VERSION 3.5)
project(Project)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set optimization and debugging flags based on the compiler
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # GCC and Clang optimizations and debug info
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g -march=native -mtune=native -flto -ffast-math -fstrict-aliasing -funroll-loops -fno-rtti")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # MSVC optimizations and debug info
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /Zi /arch:AVX2 /GL /fp:fast /GS- /GF /Zc:inline /Ob2 /Oi /Ot /Ox")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /permissive- /sdl /Zc:forScope /Zc:wchar_t /Zc:inline /Zc:rvalueCast /Zc:strictStrings /analyze")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /DEBUG")  # Ensure debug symbols are in the executable
endif()

# Define source files
set(SOURCES
    src/game.cpp
    src/value.cpp
    src/parse.cpp
    src/nn.cpp
    src/parse.cpp
    src/main.cpp
)

# Add the executable target
add_executable(runme ${SOURCES})

