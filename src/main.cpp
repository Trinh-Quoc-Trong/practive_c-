#include "core/ecs.hpp"
#include "rendering/vulkan_renderer.hpp"
#include "scripting/lua_system.hpp"
#include "core/input.hpp" // Include InputManager
#include "core/components.hpp"
#include "core/camera_control.hpp" // Include CameraControl
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    // Khởi tạo GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Tạo cửa sổ
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "PhysX Engine", nullptr, nullptr);
    
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Khởi tạo InputManager
    PhysX::InputManager::init(window);

    // Khởi tạo renderer
    PhysX::VulkanRenderer renderer(window); // Pass the window here
    try {
        renderer.init();
    } catch (const std::exception& e) {
        std::cerr << "Renderer initialization failed: " << e.what() << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    
    // Khởi tạo scene và scripting
    PhysX::Scene scene;
    PhysX::LuaSystem luaSystem;
    luaSystem.bindEngineAPI(scene);
    
    // Tạo Camera entity
    auto cameraEntity = scene.createEntity();
    cameraEntity.addComponent<Transform>(glm::vec3(0.0f, 0.0f, 3.0f));
    cameraEntity.addComponent<Camera>();

    // Tạo CameraControl
    PhysX::CameraControl cameraControl(cameraEntity, window);

    // Tải script khởi tạo
    luaSystem.executeScript("init.lua");
    
    // Vòng lặp chính
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Xử lý input (ví dụ: thoát khi nhấn ESC)
        if (PhysX::InputManager::isKeyPressed(PhysX::KeyCode::KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, true);
        }

        // Cập nhật Camera
        cameraControl.update(0.016f); // Giả sử deltaTime cố định

        // Cập nhật vật lý
        scene.update(0.016f); // 60 FPS
        
        // Render
        renderer.render();
    }
    
    // Dọn dẹp
    renderer.cleanup();
    PhysX::InputManager::shutdown(); // Dọn dẹp InputManager
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
} 