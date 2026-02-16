#include "common.h"

// Callback para redimensionar ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Procesar entrada de teclado
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main(int argc, char** argv)
{
    // Inicializar GLFW
    if (!glfwInit())
    {
        std::cerr << "Error: No se pudo inicializar GLFW" << std::endl;
        return -1;
    }

    // Configurar GLFW - OpenGL version 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Crear ventana GLFW
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Programacion Grafica 2024", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Error: No se pudo crear la ventana GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Inicializar GLAD
    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        std::cerr << "Error: No se pudo inicializar GLAD" << std::endl;
        return -1;
    }

    // Mostrar informacion de OpenGL
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // Configurar viewport inicial
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    // Bucle de renderizado
    while (!glfwWindowShouldClose(window))
    {
        // Procesar entrada
        processInput(window);

        // Renderizar
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Intercambiar buffers y procesar eventos
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminar GLFW
    glfwTerminate();
    return 0;
}