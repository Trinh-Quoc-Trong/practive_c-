#include "core/camera_control.hpp"
#include <iostream>

namespace PhysX {

CameraControl::CameraControl(Entity& cameraEntity, GLFWwindow* window)
    : cameraEntity_(cameraEntity), window_(window) {
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void CameraControl::update(float deltaTime) {
    processKeyboardInput(deltaTime);
    processMouseInput();

    // Cập nhật ma trận view của camera entity
    Transform& transform = cameraEntity_.getComponent<Transform>();
    transform.rotation = glm::quat(glm::vec3(glm::radians(pitch_), glm::radians(yaw_), 0.0f));

    // Reconstruct front, up, right vectors from rotation
    front_ = glm::normalize(glm::vec3(
        glm::cos(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_)),
        glm::sin(glm::radians(pitch_)),
        glm::sin(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_))
    ));
    right_ = glm::normalize(glm::cross(front_, glm::vec3(0.0f, 1.0f, 0.0f))); // Recalculate right
    up_ = glm::normalize(glm::cross(right_, front_)); // Recalculate up

    cameraEntity_.getComponent<Camera>().viewMatrix = glm::lookAt(transform.position, transform.position + front_, up_);
}

void CameraControl::processKeyboardInput(float deltaTime) {
    Transform& transform = cameraEntity_.getComponent<Transform>();
    float velocity = movementSpeed_ * deltaTime;

    if (InputManager::isKeyPressed(KeyCode::KEY_W)) {
        transform.position += front_ * velocity;
    }
    if (InputManager::isKeyPressed(KeyCode::KEY_S)) {
        transform.position -= front_ * velocity;
    }
    if (InputManager::isKeyPressed(KeyCode::KEY_A)) {
        transform.position -= right_ * velocity;
    }
    if (InputManager::isKeyPressed(KeyCode::KEY_D)) {
        transform.position += right_ * velocity;
    }
    if (InputManager::isKeyPressed(KeyCode::KEY_SPACE)) {
        transform.position += up_ * velocity;
    }
    if (InputManager::isKeyPressed(KeyCode::KEY_LEFT_SHIFT)) {
        transform.position -= up_ * velocity;
    }
}

void CameraControl::processMouseInput() {
    glm::vec2 currentMousePos = InputManager::getMousePosition();
    
    if (firstMouse_) {
        lastMousePos_ = currentMousePos;
        firstMouse_ = false;
    }

    glm::vec2 mouseDelta = currentMousePos - lastMousePos_;
    lastMousePos_ = currentMousePos;

    yaw_ += mouseDelta.x * mouseSensitivity_;
    pitch_ -= mouseDelta.y * mouseSensitivity_; // Đảo ngược trục Y

    // Giới hạn pitch
    if (pitch_ > 89.0f) pitch_ = 89.0f;
    if (pitch_ < -89.0f) pitch_ = -89.0f;
}

} // namespace PhysX 