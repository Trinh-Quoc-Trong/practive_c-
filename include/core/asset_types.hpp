#pragma once

#include <string>
#include <memory>
#include <vector>

namespace PhysX {

// Forward declarations
class Mesh;
class Texture;
class Shader;

// Base Asset class (optional, for common asset properties)
class Asset {
public:
    virtual ~Asset() = default;
    std::string path;
};

class MeshAsset : public Asset {
public:
    MeshAsset(const std::string& p) { path = p; }
    std::shared_ptr<Mesh> data;
    // Logic tải mesh (ví dụ từ .obj)
};

class TextureAsset : public Asset {
public:
    TextureAsset(const std::string& p) { path = p; }
    // Thông tin texture (ví dụ: VkImage, VkImageView)
    // Logic tải texture (ví dụ từ .png, .jpg)
};

class ShaderAsset : public Asset {
public:
    ShaderAsset(const std::string& p) { path = p; }
    std::shared_ptr<Shader> data; // Có thể chứa một shared_ptr đến đối tượng Shader
    // Logic tải shader (ví dụ từ .spv)
};

// Có thể thêm các loại tài nguyên khác như Material, Sound, Animation, v.v.

} // namespace PhysX 