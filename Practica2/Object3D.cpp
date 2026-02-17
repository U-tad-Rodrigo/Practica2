#include "Object3D.h"
#include "InputManager.h"

Object3D::Object3D() {
    position = make_vector4f(0.0f, 0.0f, 0.0f, 1.0f);
    rotation = make_vector4f(0.0f, 0.0f, 0.0f, 1.0f);
    scale = make_vector4f(1.0f, 1.0f, 1.0f, 1.0f);
    modelMatrix = make_identityf();
}

void Object3D::createTriangle() {
    vertexList.clear();
    idList.clear();

    Vertex v1;
    v1.position = make_vector4f(0.0f, 0.5f, 0.0f, 1.0f);
    v1.color = make_vector4f(1.0f, 0.0f, 0.0f, 1.0f);
    vertexList.push_back(v1);

    Vertex v2;
    v2.position = make_vector4f(-0.5f, -0.5f, 0.0f, 1.0f);
    v2.color = make_vector4f(0.0f, 1.0f, 0.0f, 1.0f);
    vertexList.push_back(v2);

    Vertex v3;
    v3.position = make_vector4f(0.5f, -0.5f, 0.0f, 1.0f);
    v3.color = make_vector4f(0.0f, 0.0f, 1.0f, 1.0f);
    vertexList.push_back(v3);


    idList.push_back(0);
    idList.push_back(1);
    idList.push_back(2);
}

void Object3D::move(double timeStep) {
    if (InputManager::keyMap[GLFW_KEY_D]) {
        rotation.y += 90.0f * (float)timeStep;
    }
    if (InputManager::keyMap[GLFW_KEY_A]) {
        rotation.y -= 90.0f * (float)timeStep;
    }

    updateModelMatrix();
}

void Object3D::updateModelMatrix() {
    matrix4x4f translateMatrix = make_translate(position.x, position.y, position.z);
    matrix4x4f rotateMatrix = make_rotate(rotation.x, rotation.y, rotation.z);
    matrix4x4f scaleMatrix = make_scale(scale.x, scale.y, scale.z);
    modelMatrix = translateMatrix * rotateMatrix * scaleMatrix;
}

