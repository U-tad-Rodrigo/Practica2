// Compilar la implementación de GLAD solo en este archivo
#define GLAD_BIN
#include <glad/gl.h>

#include "Render.h"
#include "Object3D.h"

int main(int argc, char** argv)
{
    Render render(640, 480);

    render.initGL();

    if (!render.initialized) {
        std::cerr << "Error al inicializar OpenGL" << std::endl;
        return -1;
    }

    Object3D triangulo;
    triangulo.createTriangle();

    render.putObject(&triangulo);
    render.mainLoop();

    return 0;
}