#pragma once
#include <string>
#include <map>
#include <memory>
#include <stdexcept>

namespace PhysX {

template<typename T>
class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager();

    std::shared_ptr<T> loadAsset(const std::string& path);
    std::shared_ptr<T> getAsset(const std::string& path);
    void unloadAsset(const std::string& path);
    void clearAssets();

private:
    std::map<std::string, std::shared_ptr<T>> assets;
};

// Định nghĩa các chuyên môn hóa cho các loại tài nguyên cụ thể
// Ví dụ: AssetManager<Mesh>, AssetManager<Texture>, AssetManager<Shader>

} // namespace PhysX 