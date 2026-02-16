#pragma once

#include "common.h"
#include "Object3D.h"
#include "InputManager.h"

class Render {
public:
    Render(int width, int height);
    ~Render();
    typedef struct {
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
    }bufferObject_t;
    vector<Object3D*> ObjectList;
    map<unsigned int, bufferObject_t> bufferMap;
    GLFWwindow* window = nullptr;
    bool initialized = false;
    int width;
    int height;

    void initGL();
    void putObject(Object3D* obj);
    void removeObject(Object3D* obj);
    void drawGL();
    void mainLoop();
};

