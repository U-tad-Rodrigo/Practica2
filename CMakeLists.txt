cmake_minimum_required(VERSION 3.16)
project(ProgGrafica_2024)

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
# PROYECTO: ProgGrafica_2024
# ============================================================================
add_executable(Practica2
        ProgGrafica_2024/MainPractica2.cpp
        ProgGrafica_2024/common.h
        ProgGrafica_2024/Vertex.h
        ProgGrafica_2024/InputManager.cpp
        ProgGrafica_2024/InputManager.h
        ProgGrafica_2024/Object3D.cpp
        ProgGrafica_2024/Object3D.h
        ProgGrafica_2024/libMath.cpp
        ProgGrafica_2024/libMath.h
        ProgGrafica_2024/Render.cpp
        ProgGrafica_2024/Render.h
)
target_include_directories(Practica2 PRIVATE ${CMAKE_SOURCE_DIR}/Practica2)
target_link_libraries(Practica2 glfw3 opengl32)
