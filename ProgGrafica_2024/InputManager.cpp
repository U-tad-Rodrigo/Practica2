//
// Created by Rodrigo on 03/02/2026.
//

#include "InputManager.h"

// Incluimos solo lo necesario para no reintroducir la implementación de GLAD
#include <GLFW/glfw3.h>

GLFWwindow* InputManager::window = nullptr;
std::map<int,bool> InputManager::keyMap;

void InputManager::initInputManager(GLFWwindow* win) {
    glfwSetKeyCallback(win, keyboardManager);
    window = win;
}
void InputManager::keyboardManager(GLFWwindow* win, int key, int scancode, int action, int mods) {
    switch (action) {
        case GLFW_PRESS: {
            keyMap[key] = true;
        } break;
        case GLFW_RELEASE: {
            keyMap[key] = false;
        } break;
        default: {
        } break;
    }
}

void InputManager::updateInputs() {
    glfwPollEvents();
}