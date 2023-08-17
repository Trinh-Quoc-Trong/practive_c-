#include "core/ecs.hpp"
#include "core/components.hpp" // Include components.hpp
#include "physics/rigidbody.hpp"
#include "physics/collision.hpp" // Include collision.hpp

namespace PhysX {
void Scene::update(float deltaTime) {
    // Cập nhật transform
    auto transformView = registry.view<Transform>();
    for (auto entity : transformView) {
        auto& transform = transformView.get<Transform>(entity);
        // Logic cập nhật transform...
    }
    
    // Cập nhật vật lý
    auto physicsView = registry.view<RigidBody>();
    for (auto entity : physicsView) {
        auto& rigidbody = physicsView.get<RigidBody>(entity);
        rigidbody.integrate(deltaTime);
    }

    // Phát hiện va chạm (ví dụ cơ bản AABB)
    auto colliderView = registry.view<Transform, Collider>();
    for (auto entityA : colliderView) {
        for (auto entityB : colliderView) {
            if (entityA == entityB) continue;

            auto& transformA = colliderView.get<Transform>(entityA);
            auto& colliderA = colliderView.get<Collider>(entityA);
            AABB aabbA = calculateAABB(transformA, colliderA);

            auto& transformB = colliderView.get<Transform>(entityB);
            auto& colliderB = colliderView.get<Collider>(entityB);
            AABB aabbB = calculateAABB(transformB, colliderB);

            if (intersectAABB(aabbA, aabbB)) {
                // Xử lý va chạm (ví dụ: in ra console)
                std::cout << "Collision detected between entities!\n";
            }
        }
    }

    // Cập nhật hệ thống hạt (Particle System)
    particleSystem.update(deltaTime);
}
} // namespace PhysX 