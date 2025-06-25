cmake_minimum_required(VERSION 3.25)
project(SudokuGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable static linking
add_definitions(-DSFML_STATIC)

# Source files
set(SOURCES
    src/main.cpp
    src/UI.cpp
    src/Solver.cpp
)

# Include directories
include_directories(
    include
    C:/msys64/ucrt64/include
)

# Link directories
link_directories(C:/msys64/ucrt64/lib)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Create executable
add_executable(SudokuGame ${SOURCES})

# Link SFML static libraries
target_link_libraries(SudokuGame
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
    freetype
    jpeg
    opengl32
    gdi32
    winmm
)

target_include_directories(SudokuGame PRIVATE ${PROJECT_SOURCE_DIR}/include)

