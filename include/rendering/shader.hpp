#pragma once
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace PhysX {

class Shader {
public:
    Shader();
    ~Shader();

    void loadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    VkPipelineShaderStageCreateInfo createShaderStage(VkShaderModule shaderModule, VkShaderStageFlagBits stage);

private:
    VkShaderModule createShaderModule(const std::vector<char>& code);
    std::vector<char> readFile(const std::string& filename);

private:
    VkDevice device; // Cần được truyền vào hoặc lấy từ renderer
    // Các shader module
    VkShaderModule vertexShaderModule;
    VkShaderModule fragmentShaderModule;
};

} // namespace PhysX 