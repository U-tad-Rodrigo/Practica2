#include "Render.h"


Render::Render(int width, int height) : width(width), height(height), window(nullptr), initialized(false) {
}

Render::~Render() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Render::initGL() {
    initialized = false;

    if (!glfwInit()) {
        std::cerr << "ERROR: Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, "Practica 2 - Triangulo Rotando", nullptr, nullptr);

    if (!window) {
        std::cerr << "ERROR: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "ERROR: Failed to initialize OpenGL/GLAD" << std::endl;
        glfwTerminate();
        return;
    }

    glViewport(0, 0, width, height);
    glEnable(GL_VERTEX_ARRAY);

    InputManager::initInputManager(window);

    initialized = true;
}

void Render::putObject(Object3D* obj) {
    if (!obj) return;

    bufferObject bo;
    glGenVertexArrays(1, &bo.VAO);
    glGenBuffers(1, &bo.VBO);
    glGenBuffers(1, &bo.EBO);

    glBindVertexArray(bo.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, bo.VBO);
    glBufferData(GL_ARRAY_BUFFER, obj->vertexList.size() * sizeof(Vertex), obj->vertexList.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj->idList.size() * sizeof(int), obj->idList.data(), GL_STATIC_DRAW);

    glVertexPointer(4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glBindVertexArray(0);

    bufferObjects[obj] = bo;
    objectList.push_back(obj);
}

void Render::removeObject(Object3D* obj) {
    if (!obj) return;

    if (bufferObjects.count(obj)) {
        bufferObject& bo = bufferObjects[obj];
        glDeleteBuffers(1, &bo.VBO);
        glDeleteBuffers(1, &bo.EBO);
        glDeleteVertexArrays(1, &bo.VAO);
        bufferObjects.erase(obj);
    }

    for (size_t i = 0; i < objectList.size(); i++) {
        if (objectList[i] == obj) {
            objectList.erase(objectList.begin() + i);
            break;
        }
    }
}

void Render::drawGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (Object3D* obj : objectList) {
        if (!bufferObjects.count(obj)) continue;

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMultMatrixf(obj->modelMatrix.mat);

        glBindVertexArray(bufferObjects[obj].VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObjects[obj].EBO);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glDrawElements(GL_TRIANGLES, obj->idList.size(), GL_UNSIGNED_INT, 0);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);

        glBindVertexArray(0);

        glPopMatrix();
    }
}

void Render::mainLoop() {
    if (!initialized) {
        std::cerr << "ERROR: Render not initialized" << std::endl;
        return;
    }

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        InputManager::updateInputs();

        for (Object3D* obj : objectList) {
            obj->move(deltaTime);
        }

        drawGL();

        glfwSwapBuffers(window);
    }
}

