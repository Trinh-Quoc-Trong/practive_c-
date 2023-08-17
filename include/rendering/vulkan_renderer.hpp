#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include "rendering/shader.hpp"
#include "rendering/mesh.hpp"
#include <optional> // New include for std::optional
#include <set>      // New include for std::set

namespace PhysX {

class VulkanRenderer {
public:
    VulkanRenderer(GLFWwindow* glfwWindow); // Modified constructor
    ~VulkanRenderer();
    
    void init();
    void render();
    void cleanup();
    
private:
    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void createVertexBuffer(); // Mới
    void createIndexBuffer();  // Mới

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;

    // Vertex/Index buffers
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    // Shader object
    Shader mainShader;

    // Current frame in flight
    uint32_t currentFrame = 0;
    const int MAX_FRAMES_IN_FLIGHT = 2;

    // UBOs
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;

    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    // For draw call
    std::vector<uint32_t> indices; // Store indices from createIndexBuffer

    // ... các thành phần khác...

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size); // New copy buffer function

    void createUniformBuffers();
    void createDescriptorSetLayout();
    void createDescriptorPool();
    void createDescriptorSets();

};

// Định nghĩa UniformBufferObject struct
struct UniformBufferObject {
    glm::mat4 model; // Model matrix
    glm::mat4 view;  // View matrix
    glm::mat4 proj;  // Projection matrix
};

} // namespace PhysX 