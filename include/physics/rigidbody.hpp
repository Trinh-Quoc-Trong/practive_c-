#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace PhysX {

struct RigidBody {
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    glm::quat orientation = {1.0f, 0.0f, 0.0f, 0.0f};
    glm::vec3 velocity = {0.0f, 0.0f, 0.0f};
    glm::vec3 angularVelocity = {0.0f, 0.0f, 0.0f};
    glm::vec3 force = {0.0f, 0.0f, 0.0f};
    glm::vec3 torque = {0.0f, 0.0f, 0.0f};
    float mass = 1.0f;
    glm::mat3 inertiaTensor = glm::mat3(1.0f);
    
    void integrate(float deltaTime);
    void applyForce(const glm::vec3& force, const glm::vec3& point);
};

} // namespace PhysX 