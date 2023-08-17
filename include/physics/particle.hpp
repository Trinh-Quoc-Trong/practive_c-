#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace PhysX {

struct Particle {
    glm::vec3 position;
    glm::vec3 oldPosition; // For Verlet integration
    glm::vec3 velocity; // For explicit Euler (alternative)
    glm::vec3 acceleration;
    float mass;
    bool fixed; // If particle is fixed in space
};

struct SpringConstraint {
    int particleAIndex;
    int particleBIndex;
    float restLength;
    float stiffness; // Stiffness of the spring
};

class ParticleSystem {
public:
    ParticleSystem();

    void addParticle(const Particle& particle);
    void addSpringConstraint(const SpringConstraint& constraint);
    void update(float deltaTime, int iterations = 5);

private:
    std::vector<Particle> particles_;
    std::vector<SpringConstraint> constraints_;

    void applyGravity();
    void integrate(float deltaTime);
    void satisfyConstraints();
};

} // namespace PhysX 