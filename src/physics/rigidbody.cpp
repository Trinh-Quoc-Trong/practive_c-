#include "physics/rigidbody.hpp"
#include <glm/gtx/quaternion.hpp>

namespace PhysX {

void RigidBody::integrate(float deltaTime) {
    // Cập nhật vận tốc
    velocity += (force / mass) * deltaTime;
    angularVelocity += inertiaTensor * torque * deltaTime;
    
    // Cập nhật vị trí
    position += velocity * deltaTime;
    
    // Cập nhật hướng
    glm::quat dq = glm::quat(0.0f, angularVelocity.x, angularVelocity.y, angularVelocity.z) * orientation;
    orientation += 0.5f * deltaTime * dq;
    orientation = glm::normalize(orientation);
    
    // Reset lực
    force = glm::vec3(0.0f);
    torque = glm::vec3(0.0f);
}

void RigidBody::applyForce(const glm::vec3& force, const glm::vec3& point) {
    this->force += force;
    this->torque += glm::cross(point - position, force);
}
} // namespace PhysX 