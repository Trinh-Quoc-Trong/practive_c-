#include "physics/collision.hpp"
#include <algorithm>

namespace PhysX {

bool intersectAABB(const AABB& a, const AABB& b) {
    return (a.min.x <= b.max.x && a.max.x >= b.min.x) &&
           (a.min.y <= b.max.y && a.max.y >= b.min.y) &&
           (a.min.z <= b.max.z && a.max.z >= b.min.z);
}

AABB calculateAABB(const Transform& transform, const Collider& collider) {
    // Giả định collider là một hộp có kích thước 1x1x1 cho đơn giản ban đầu
    // Sau này sẽ đọc kích thước từ collider data
    glm::vec3 halfExtents = glm::vec3(0.5f, 0.5f, 0.5f) * transform.scale;
    glm::vec3 center = transform.position + collider.offset;

    AABB aabb;
    aabb.min = center - halfExtents;
    aabb.max = center + halfExtents;
    return aabb;
}

} // namespace PhysX 