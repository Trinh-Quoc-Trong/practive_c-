#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace PhysX {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription();
    static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
};

class Mesh {
public:
    Mesh() = default;
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

    const std::vector<Vertex>& getVertices() const { return vertices_; }
    const std::vector<uint32_t>& getIndices() const { return indices_; }

private:
    std::vector<Vertex> vertices_;
    std::vector<uint32_t> indices_;
};

} // namespace PhysX 