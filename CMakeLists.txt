cmake_minimum_required(VERSION 3.16)
project(Practica2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/externalLibs/glad/inc
    ${CMAKE_SOURCE_DIR}/externalLibs/glfw/inc
    ${CMAKE_SOURCE_DIR}/externalLibs/glm/inc
)

# Link directories
link_directories(${CMAKE_SOURCE_DIR}/externalLibs/glfw/lib)

# Source files
set(SOURCES
    Practica2/MainPractica2.cpp
    Practica2/common.h
    Practica2/Vertex.h
    Practica2/InputManager.h
    Practica2/InputManager.cpp
    Practica2/Object3D.h
    Practica2/Object3D.cpp
    Practica2/Render.h
    Practica2/Render.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    glfw3
    opengl32
)
