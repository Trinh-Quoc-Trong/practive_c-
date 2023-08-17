#include "rendering/shader.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace PhysX {

Shader::Shader() : device(VK_NULL_HANDLE), vertexShaderModule(VK_NULL_HANDLE), fragmentShaderModule(VK_NULL_HANDLE) {}

Shader::~Shader() {
    if (device != VK_NULL_HANDLE) {
        if (vertexShaderModule != VK_NULL_HANDLE) {
            vkDestroyShaderModule(device, vertexShaderModule, nullptr);
        }
        if (fragmentShaderModule != VK_NULL_HANDLE) {
            vkDestroyShaderModule(device, fragmentShaderModule, nullptr);
        }
    }
}

void Shader::loadFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    auto vertexCode = readFile(vertexShaderPath);
    auto fragmentCode = readFile(fragmentShaderPath);

    vertexShaderModule = createShaderModule(vertexCode);
    fragmentShaderModule = createShaderModule(fragmentCode);
}

VkShaderModule Shader::createShaderModule(const std::vector<char>& code) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }
    return shaderModule;
}

std::vector<char> Shader::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file: " + filename);
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
}

VkPipelineShaderStageCreateInfo Shader::createShaderStage(VkShaderModule shaderModule, VkShaderStageFlagBits stage) {
    VkPipelineShaderStageCreateInfo shaderStageInfo{};
    shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStageInfo.stage = stage;
    shaderStageInfo.module = shaderModule;
    shaderStageInfo.pName = "main";
    return shaderStageInfo;
}

} // namespace PhysX 