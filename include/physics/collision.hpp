#pragma once
#include "core/components.hpp"
#include <vector>

namespace PhysX {

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

// Hàm phát hiện va chạm AABB-AABB
bool intersectAABB(const AABB& a, const AABB& b);

// Hàm tính toán AABB từ Transform và Collider (giả định Collider là Box tạm thời)
AABB calculateAABB(const Transform& transform, const Collider& collider);

} // namespace PhysX 