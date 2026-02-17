#pragma once

#include "common.h"
#include "Object3D.h"
#include "InputManager.h"

typedef struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
} bufferObject;

class Render {
public:
    Render(int width, int height);
    ~Render();

    GLFWwindow* window;
    vector<Object3D*> objectList;
    map<Object3D*, bufferObject> bufferObjects;
    int width;
    int height;
    bool initialized;

    void initGL();
    void putObject(Object3D* obj);
    void removeObject(Object3D* obj);
    void drawGL();
    void mainLoop();
};

