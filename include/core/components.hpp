#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace PhysX {

struct Transform {
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    glm::quat rotation = {1.0f, 0.0f, 0.0f, 0.0f};
    glm::vec3 scale = {1.0f, 1.0f, 1.0f};
};

// Các component khác sẽ được thêm vào đây (ví dụ: MeshRenderer, Camera, Light)

struct Collider {
    enum Type { Sphere, Box, Mesh };
    Type type;
    // Dữ liệu cụ thể cho từng loại collider (ví dụ: bán kính, kích thước hộp)
    glm::vec3 offset = {0.0f, 0.0f, 0.0f}; // Offset so với transform của entity
    // Tạm thời, để đơn giản, chỉ định nghĩa các trường chung
    // Sau này sẽ dùng std::variant hoặc kế thừa để xử lý từng loại cụ thể
};

struct MeshRenderer {
    std::string meshPath; // Đường dẫn đến file model (ví dụ: .obj, .gltf)
    std::string materialPath; // Đường dẫn đến vật liệu (ví dụ: .mtl, hoặc định nghĩa PBR)
};

struct Camera {
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix; // Sẽ được tính từ Transform component
    float fov = 60.0f;
    float nearClip = 0.1f;
    float farClip = 1000.0f;
};

} // namespace PhysX 