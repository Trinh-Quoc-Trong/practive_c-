#pragma once
#include <entt/entt.hpp>
#include <memory>

namespace PhysX {

class Entity {
public:
    Entity(entt::registry& registry) : registry(registry), entity(registry.create()) {}
    
    template<typename T, typename... Args>
    T& addComponent(Args&&... args) {
        return registry.emplace<T>(entity, std::forward<Args>(args)...);
    }
    
    template<typename T>
    T& getComponent() {
        return registry.get<T>(entity);
    }
    
    template<typename T>
    bool hasComponent() {
        return registry.all_of<T>(entity);
    }
    
private:
    entt::registry& registry;
    entt::entity entity;
};

class Scene {
public:
    Entity createEntity() {
        return Entity(registry);
    }
    
    void update(float deltaTime);

private:
    entt::registry registry;
    ParticleSystem particleSystem; // Thêm ParticleSystem vào Scene
};
} // namespace PhysX 