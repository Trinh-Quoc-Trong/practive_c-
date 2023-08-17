#include "core/input.hpp"
#include <iostream>

namespace PhysX {

std::map<int, bool> InputManager::s_keys;
std::map<int, bool> InputManager::s_mouseButtons;
glm::vec2 InputManager::s_lastMousePos;
glm::vec2 InputManager::s_currentMousePos;
bool InputManager::s_firstMouseInput = true;

void InputManager::init(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
}

void InputManager::shutdown() {
    s_keys.clear();
    s_mouseButtons.clear();
}

bool InputManager::isKeyPressed(KeyCode key) {
    return s_keys[static_cast<int>(key)];
}

bool InputManager::isMouseButtonPressed(MouseButton button) {
    return s_mouseButtons[static_cast<int>(button)];
}

glm::vec2 InputManager::getMousePosition() {
    return s_currentMousePos;
}

glm::vec2 InputManager::getMouseDelta() {
    if (s_firstMouseInput) {
        s_firstMouseInput = false;
        return glm::vec2(0.0f, 0.0f);
    }
    glm::vec2 delta = s_currentMousePos - s_lastMousePos;
    s_lastMousePos = s_currentMousePos; // Cập nhật lastMousePos cho frame tiếp theo
    return delta;
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    s_keys[key] = (action == GLFW_PRESS || action == GLFW_REPEAT);
}

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    s_mouseButtons[button] = (action == GLFW_PRESS);
}

void InputManager::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
    s_currentMousePos = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));
    if (s_firstMouseInput) {
        s_lastMousePos = s_currentMousePos;
    }
}

} // namespace PhysX 