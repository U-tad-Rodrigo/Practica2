# Preguntas Probables de Examen — Práctica 2

> Basado en el código real del proyecto. Cada solución indica **qué archivo tocar** y **qué cambiar exactamente**.

---

## 1. Mover el triángulo con WASD

**Pregunta:** *"Haz que el triángulo se mueva por pantalla con las teclas WASD"*

**Archivo:** `Object3D.cpp` → método `move()`

```cpp
void Object3D::move(double timeStep) {
    float speed = 1.0f;

    if (InputManager::keyMap[GLFW_KEY_W]) position.y += speed * (float)timeStep;
    if (InputManager::keyMap[GLFW_KEY_S]) position.y -= speed * (float)timeStep;
    if (InputManager::keyMap[GLFW_KEY_A]) position.x -= speed * (float)timeStep;
    if (InputManager::keyMap[GLFW_KEY_D]) position.x += speed * (float)timeStep;

    updateModelMatrix();
}
```

---

## 2. Rotar en los 3 ejes (X con flechas, Z con Q/E)

**Pregunta:** *"Añade rotación en el eje X con las teclas de flecha arriba/abajo, y en Z con Q/E"*

**Archivo:** `Object3D.cpp` → método `move()`

```cpp
void Object3D::move(double timeStep) {
    float rotSpeed = 90.0f;

    // Eje Y — ya existente
    if (InputManager::keyMap[GLFW_KEY_A]) rotation.y -= rotSpeed * (float)timeStep;
    if (InputManager::keyMap[GLFW_KEY_D]) rotation.y += rotSpeed * (float)timeStep;

    // Eje X — flechas arriba/abajo
    if (InputManager::keyMap[GLFW_KEY_UP])   rotation.x += rotSpeed * (float)timeStep;
    if (InputManager::keyMap[GLFW_KEY_DOWN])  rotation.x -= rotSpeed * (float)timeStep;

    // Eje Z — Q y E
    if (InputManager::keyMap[GLFW_KEY_Q]) rotation.z += rotSpeed * (float)timeStep;
    if (InputManager::keyMap[GLFW_KEY_E]) rotation.z -= rotSpeed * (float)timeStep;

    updateModelMatrix();
}
```

---

## 3. Escalar el triángulo con teclas + / -

**Pregunta:** *"Haz que el triángulo crezca y se encoja con las teclas + y -"*

**Archivo:** `Object3D.cpp` → método `move()`

```cpp
void Object3D::move(double timeStep) {
    float scaleSpeed = 1.0f;

    if (InputManager::keyMap[GLFW_KEY_KP_ADD])      scale.x += scaleSpeed * (float)timeStep;
    if (InputManager::keyMap[GLFW_KEY_KP_SUBTRACT])  scale.x -= scaleSpeed * (float)timeStep;

    // Escala uniforme en los 3 ejes
    scale.y = scale.x;
    scale.z = scale.x;

    updateModelMatrix();
}
```

---

## 4. Añadir un segundo triángulo que rote independientemente

**Pregunta:** *"Añade un segundo triángulo que rote en sentido contrario al primero"*

**Archivo:** `MainPractica2.cpp`

```cpp
int main(int argc, char** argv) {
    Render render(640, 480);
    render.initGL();

    if (!render.initialized) return -1;

    Object3D triangulo1;
    triangulo1.createTriangle();
    // Desplazarlo a la izquierda para que no se solapen
    triangulo1.position.x = -0.5f;

    Object3D triangulo2;
    triangulo2.createTriangle();
    triangulo2.position.x = 0.5f;

    render.putObject(&triangulo1);
    render.putObject(&triangulo2);
    render.mainLoop();

    return 0;
}
```

Para que el segundo rote en sentido contrario, crear una clase hija:

**Archivo nuevo:** `TrianguloInverso.h`

```cpp
#pragma once
#include "Object3D.h"

class TrianguloInverso : public Object3D {
public:
    void move(double timeStep) override {
        if (InputManager::keyMap[GLFW_KEY_D]) rotation.y -= 90.0f * (float)timeStep; // invertido
        if (InputManager::keyMap[GLFW_KEY_A]) rotation.y += 90.0f * (float)timeStep;
        updateModelMatrix();
    }
};
```

Uso en `MainPractica2.cpp`:

```cpp
Object3D triangulo1;
triangulo1.createTriangle();
triangulo1.position.x = -0.5f;

TrianguloInverso triangulo2;
triangulo2.createTriangle();
triangulo2.position.x = 0.5f;

render.putObject(&triangulo1);
render.putObject(&triangulo2);
```

---

## 5. Cambiar a un cuadrado (quad) en lugar de triángulo

**Pregunta:** *"Cambia el triángulo por un cuadrado"*

**Archivo:** `Object3D.h` → añadir declaración:

```cpp
void createQuad();
```

**Archivo:** `Object3D.cpp` → añadir implementación:

```cpp
void Object3D::createQuad() {
    vertexList.clear();
    idList.clear();

    //    0----3
    //    |  / |
    //    | /  |
    //    1----2

    Vertex v0; v0.position = make_vector4f(-0.5f,  0.5f, 0.0f, 1.0f); v0.color = make_vector4f(1.0f, 0.0f, 0.0f, 1.0f);
    Vertex v1; v1.position = make_vector4f(-0.5f, -0.5f, 0.0f, 1.0f); v1.color = make_vector4f(0.0f, 1.0f, 0.0f, 1.0f);
    Vertex v2; v2.position = make_vector4f( 0.5f, -0.5f, 0.0f, 1.0f); v2.color = make_vector4f(0.0f, 0.0f, 1.0f, 1.0f);
    Vertex v3; v3.position = make_vector4f( 0.5f,  0.5f, 0.0f, 1.0f); v3.color = make_vector4f(1.0f, 1.0f, 0.0f, 1.0f);

    vertexList.push_back(v0);
    vertexList.push_back(v1);
    vertexList.push_back(v2);
    vertexList.push_back(v3);

    // Dos triángulos que forman el cuadrado
    idList = {0, 1, 2,  0, 2, 3};
}
```

**Archivo:** `MainPractica2.cpp` → cambiar `createTriangle()` por `createQuad()`:

```cpp
Object3D cuadrado;
cuadrado.createQuad();   // <-- en vez de createTriangle()
render.putObject(&cuadrado);
```

---

## 6. Rotar alrededor de un punto que no es el origen (pivot)

**Pregunta:** *"Haz que el triángulo rote alrededor del punto (0.5, 0, 0) en lugar del origen"*

**Archivo:** `Object3D.cpp` → método `updateModelMatrix()`

```cpp
void Object3D::updateModelMatrix() {
    // Punto de pivote
    float px = 0.5f, py = 0.0f, pz = 0.0f;

    matrix4x4f toPivot    = make_translate(-px, -py, -pz);  // mover al origen
    matrix4x4f rotMatrix  = make_rotate(rotation.x, rotation.y, rotation.z);
    matrix4x4f fromPivot  = make_translate(px, py, pz);     // volver al pivot
    matrix4x4f tMatrix    = make_translate(position.x, position.y, position.z);
    matrix4x4f sMatrix    = make_scale(scale.x, scale.y, scale.z);

    // Orden: escalar → ir al pivot → rotar → volver → trasladar
    modelMatrix = tMatrix * fromPivot * rotMatrix * toPivot * sMatrix;
}
```

---

## 7. Movimiento + Rotación simultáneos (WASD mueve, A/D también rota)

**Pregunta:** *"El objeto debe moverse con WASD y rotar con las flechas izquierda/derecha"*

**Archivo:** `Object3D.cpp` → método `move()`

```cpp
void Object3D::move(double timeStep) {
    float speed    = 1.0f;
    float rotSpeed = 90.0f;

    // Movimiento
    if (InputManager::keyMap[GLFW_KEY_W]) position.y += speed * (float)timeStep;
    if (InputManager::keyMap[GLFW_KEY_S]) position.y -= speed * (float)timeStep;
    if (InputManager::keyMap[GLFW_KEY_A]) position.x -= speed * (float)timeStep;
    if (InputManager::keyMap[GLFW_KEY_D]) position.x += speed * (float)timeStep;

    // Rotación
    if (InputManager::keyMap[GLFW_KEY_LEFT])  rotation.y -= rotSpeed * (float)timeStep;
    if (InputManager::keyMap[GLFW_KEY_RIGHT]) rotation.y += rotSpeed * (float)timeStep;

    updateModelMatrix();
}
```

---

## 8. Clase hija que extiende Object3D con comportamiento propio

**Pregunta:** *"Crea una clase TrianguloRapido que rote el doble de rápido que Object3D"*

> Esto prueba que entiendes `virtual` + herencia.

**Archivo nuevo:** `TrianguloRapido.h`

```cpp
#pragma once
#include "Object3D.h"
#include "InputManager.h"

class TrianguloRapido : public Object3D {
public:
    void move(double timeStep) override {
        if (InputManager::keyMap[GLFW_KEY_D]) rotation.y += 180.0f * (float)timeStep; // x2
        if (InputManager::keyMap[GLFW_KEY_A]) rotation.y -= 180.0f * (float)timeStep;
        updateModelMatrix();
    }
};
```

Uso en `MainPractica2.cpp`:

```cpp
#include "TrianguloRapido.h"

// ...
TrianguloRapido triangulo;
triangulo.createTriangle();
render.putObject(&triangulo);
```

---

## Resumen rápido

| Pregunta probable | Archivo a tocar | Qué cambiar |
|---|---|---|
| Mover con WASD | `Object3D.cpp` → `move()` | `position.x/y` |
| Rotar en 3 ejes | `Object3D.cpp` → `move()` | `rotation.x/y/z` con más teclas |
| Escalar con teclas | `Object3D.cpp` → `move()` | `scale.x/y/z` |
| Segundo triángulo | `MainPractica2.cpp` | Nueva instancia `Object3D` |
| Cuadrado en vez de triángulo | `Object3D.h/.cpp` + `Main` | Nuevo método `createQuad()` |
| Rotar sobre pivot | `Object3D.cpp` → `updateModelMatrix()` | Orden de matrices con offset |
| Movimiento + rotación | `Object3D.cpp` → `move()` | Combinar teclas |
| Clase hija | Nuevo `.h` hereda `Object3D` | Override de `move()` |

