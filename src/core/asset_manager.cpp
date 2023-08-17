#include "core/asset_manager.hpp"
#include "core/asset_types.hpp" // Include asset types
#include "rendering/mesh.hpp"
#include "rendering/shader.hpp"
#include <iostream>

namespace PhysX {

template<typename T>
AssetManager<T>::~AssetManager() {
    clearAssets();
}

template<typename T>
std::shared_ptr<T> AssetManager<T>::loadAsset(const std::string& path) {
    if (assets.count(path)) {
        std::cerr << "Asset already loaded: " << path << "\n";
        return assets[path];
    }
    
    std::shared_ptr<T> newAsset = std::make_shared<T>();
    newAsset->path = path; // Đặt đường dẫn cho tài sản
    // Logic tải tài sản thực tế sẽ ở đây (ví dụ: đọc từ file)
    // Đối với ví dụ, chúng ta chỉ tạo một đối tượng trống

    // Ví dụ về logic tải tài sản cụ thể
    if constexpr (std::is_same_v<T, MeshAsset>) {
        // Load mesh using tinyobjloader or similar
        std::cout << "Loading mesh asset: " << path << "\n";
        // Giả sử tải mesh thành công, tạo một Mesh object đơn giản
        std::vector<Vertex> vertices = {{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}, {{0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}}};
        std::vector<uint32_t> indices = {0, 1, 2};
        newAsset->data = std::make_shared<Mesh>(vertices, indices);
    } else if constexpr (std::is_same_v<T, ShaderAsset>) {
        std::cout << "Loading shader asset: " << path << "\n";
        newAsset->data = std::make_shared<Shader>();
        // Shader loadFromFile needs a device, so this is just a placeholder
        // newAsset->data->loadFromFile(path + ".vert", path + ".frag");
    } else if constexpr (std::is_same_v<T, TextureAsset>) {
        std::cout << "Loading texture asset: " << path << "\n";
        // Load texture
    }

    assets[path] = newAsset;
    std::cout << "Loaded asset: " << path << "\n";
    return newAsset;
}

template<typename T>
std::shared_ptr<T> AssetManager<T>::getAsset(const std::string& path) {
    auto it = assets.find(path);
    if (it != assets.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Asset not found: " + path);
    }
}

template<typename T>
void AssetManager<T>::unloadAsset(const std::string& path) {
    auto it = assets.find(path);
    if (it != assets.end()) {
        assets.erase(it);
        std::cout << "Unloaded asset: " << path << "\n";
    }
}

template<typename T>
void AssetManager<T>::clearAssets() {
    assets.clear();
    std::cout << "All assets cleared.\n";
}

// Explicit instantiations for common asset types (required for template definitions in .cpp)
template class AssetManager<MeshAsset>;
template class AssetManager<TextureAsset>;
template class AssetManager<ShaderAsset>;

} // namespace PhysX 