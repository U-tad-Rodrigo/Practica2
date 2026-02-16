#include "Render.h"
#include "InputManager.h"

Render::Render(int width, int height) {
    this->width = width;
    this->height = height;
    this->window = nullptr;
}

Render::~Render() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Render::initGL() {
    initialized = false;
    if (!glfwInit())
    {
        std::cerr << "ERROR: Failed to initialize glfw" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    this->window = glfwCreateWindow(width, height, "Practica 2", nullptr, nullptr);
    if (!window) {
        std::cerr << "ERROR: Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "ERROR: Failed to initialize OpenGL" << std::endl;
        glfwTerminate();
        return;
    }
    InputManager::initInputManager(window);
    initialized = true;
}

void Render::putObject(Object3D* obj) {
    bufferObject_t bo = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    glGenVertexArrays(1, &bo.VAO);
    glGenBuffers(1, &bo.VBO);
    glGenBuffers(1, &bo.EBO);

    glBindVertexArray(bo.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, bo.VBO);
    glBufferData(GL_ARRAY_BUFFER, obj->vertexList.size() * sizeof(vertex_t), obj->vertexList.data(), GL_STATIC_DRAW);

}

void Render::removeObject(Object3D* obj) {

}

void Render::drawGL() {

}

void Render::mainLoop() {

}

