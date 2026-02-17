cmake_minimum_required(VERSION 3.16)
project(Practica2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ============================================================================
# DIRECTORIOS DE INCLUSIÓN Y LIBRERÍAS EXTERNAS
# ============================================================================
include_directories(
        ${CMAKE_SOURCE_DIR}/externalLibs/glad/inc
        ${CMAKE_SOURCE_DIR}/externalLibs/glfw/inc
        ${CMAKE_SOURCE_DIR}/externalLibs/glm/inc
)

link_directories(${CMAKE_SOURCE_DIR}/externalLibs/glfw/lib)

# ============================================================================
# PROYECTO: Practica2
# ============================================================================
add_executable(Practica2
        Practica2/MainPractica2.cpp
        Practica2/common.h
        Practica2/Vertex.h
        Practica2/InputManager.cpp
        Practica2/InputManager.h
        Practica2/Object3D.cpp
        Practica2/Object3D.h
        Practica2/libMath.cpp
        Practica2/libMath.h
        Practica2/Render.cpp
        Practica2/Render.h
)
target_include_directories(Practica2 PRIVATE ${CMAKE_SOURCE_DIR}/Practica2)
target_link_libraries(Practica2 glfw3 opengl32)
