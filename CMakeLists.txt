cmake_minimum_required(VERSION 3.10)
project(CrossVoxelGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Add executable
add_executable(CrossVoxelGame src/main.cpp)

# Link libraries
target_link_libraries(CrossVoxelGame
    OpenGL::GL
    GLEW::GLEW
    glfw
)
