#include "physics/particle.hpp"
#include <glm/gtx/norm.hpp>

namespace PhysX {

ParticleSystem::ParticleSystem() {
    // Initialize with some default values or empty
}

void ParticleSystem::addParticle(const Particle& particle) {
    particles_.push_back(particle);
}

void ParticleSystem::addSpringConstraint(const SpringConstraint& constraint) {
    constraints_.push_back(constraint);
}

void ParticleSystem::update(float deltaTime, int iterations) {
    applyGravity();
    integrate(deltaTime);

    for (int i = 0; i < iterations; ++i) {
        satisfyConstraints();
    }
}

void ParticleSystem::applyGravity() {
    glm::vec3 gravity = {0.0f, -9.81f, 0.0f};
    for (auto& p : particles_) {
        if (!p.fixed) {
            p.acceleration += gravity;
        }
    }
}

void ParticleSystem::integrate(float deltaTime) {
    for (auto& p : particles_) {
        if (!p.fixed) {
            glm::vec3 tempPosition = p.position;
            p.position += (p.position - p.oldPosition) + p.acceleration * deltaTime * deltaTime;
            p.oldPosition = tempPosition;
            p.acceleration = {0.0f, 0.0f, 0.0f};
        }
    }
}

void ParticleSystem::satisfyConstraints() {
    for (const auto& c : constraints_) {
        Particle& p1 = particles_[c.particleAIndex];
        Particle& p2 = particles_[c.particleBIndex];

        glm::vec3 delta = p2.position - p1.position;
        float dist = glm::length(delta);
        float diff = (dist - c.restLength) / dist;

        glm::vec3 correction = delta * 0.5f * diff * c.stiffness;

        if (!p1.fixed) {
            p1.position += correction;
        }
        if (!p2.fixed) {
            p2.position -= correction;
        }
    }

    // Example: Ground collision
    for (auto& p : particles_) {
        if (p.position.y < 0.0f) {
            p.position.y = 0.0f; // Prevent sinking below ground
        }
    }
}

} // namespace PhysX 