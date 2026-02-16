#pragma once

#include <map>

struct GLFWwindow; // forward declaration

class InputManager {
public:
    static std::map<int,bool> keyMap; // Mapa para almacenar el estado de las teclas
    static GLFWwindow* window;
    static void initInputManager(GLFWwindow* window);
    static void keyboardManager(GLFWwindow* window, int key, int scancode, int action, int mods);
    //static void mouseButtonManager(GLFWwindow* window, int button, int action, int mods);
    static void updateInputs();
};

