#pragma once
#include "core/components.hpp"
#include "core/input.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace PhysX {

class CameraControl {
public:
    CameraControl(Entity& cameraEntity, GLFWwindow* window);

    void update(float deltaTime);

private:
    Entity& cameraEntity_;
    GLFWwindow* window_;
    
    glm::vec3 front_ = {0.0f, 0.0f, -1.0f};
    glm::vec3 up_ = {0.0f, 1.0f, 0.0f};
    glm::vec3 right_ = {1.0f, 0.0f, 0.0f};

    float yaw_ = -90.0f; // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right, so we initially rotate a bit to the left.
    float pitch_ = 0.0f;
    float movementSpeed_ = 2.5f;
    float mouseSensitivity_ = 0.1f;
    
    glm::vec2 lastMousePos_;
    bool firstMouse_ = true;

    void processKeyboardInput(float deltaTime);
    void processMouseInput();
};

} // namespace PhysX 