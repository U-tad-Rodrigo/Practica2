#pragma once

#include "libMath.h"
#include "Vertex.h"

class Object3D {
public:
    // Properties
    vec4float position;
    vec4float rotation;
    vec4float scale;
    matrix4x4f modelMatrix;
    vector<Vertex> vertexList;
    vector<int> idList;

    // Constructor
    Object3D();
    virtual ~Object3D() = default;

    // Methods
    void createTriangle();
    virtual void move(double timeStep);
    void updateModelMatrix();
};

