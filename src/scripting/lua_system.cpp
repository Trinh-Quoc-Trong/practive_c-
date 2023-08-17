#include "scripting/lua_system.hpp"
#include "core/ecs.hpp"
#include "physics/rigidbody.hpp"
#include <iostream>

namespace PhysX {

LuaSystem::LuaSystem() {
    lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table);
}

void LuaSystem::bindEngineAPI(Scene& scene) {
    // Đăng ký kiểu Vector3
    lua.new_usertype<glm::vec3>("Vector3",
        sol::constructors<glm::vec3(), glm::vec3(float, float, float)>(),
        "x", &glm::vec3::x,
        "y", &glm::vec3::y,
        "z", &glm::vec3::z,
        sol::meta_function::addition, [](const glm::vec3& a, const glm::vec3& b) { return a + b; },
        sol::meta_function::subtraction, [](const glm::vec3& a, const glm::vec3& b) { return a - b; }
    );
    
    // Đăng ký kiểu Entity
    lua.new_usertype<Entity>("Entity",
        "add_rigidbody", [](Entity& e, float mass) {
            return &e.addComponent<RigidBody>(mass);
        },
        "get_position", [](Entity& e) {
            return e.getComponent<Transform>().position;
        },
        "set_position", [](Entity& e, const glm::vec3& pos) {
            e.getComponent<Transform>().position = pos;
        },
        "add_mesh_renderer", [](Entity& e, const std::string& meshPath, const std::string& materialPath) {
            return &e.addComponent<MeshRenderer>(meshPath, materialPath);
        }
    );
    
    // Đăng ký hàm tạo entity
    lua["create_entity"] = [&scene]() -> Entity {
        return scene.createEntity();
    };

    // Đăng ký InputManager cho Lua
    lua["Input"] = lua.create_table_with(
        "is_key_pressed", sol::resolve<bool(KeyCode)>(PhysX::InputManager::isKeyPressed),
        "is_mouse_button_pressed", sol::resolve<bool(MouseButton)>(PhysX::InputManager::isMouseButtonPressed),
        "get_mouse_position", sol::resolve<glm::vec2()>(PhysX::InputManager::getMousePosition),
        "get_mouse_delta", sol::resolve<glm::vec2()>(PhysX::InputManager::getMouseDelta)
    );

    // Đăng ký enum KeyCode và MouseButton vào Lua
    lua.new_enum("KeyCode",
        "KEY_W", KeyCode::KEY_W,
        "KEY_A", KeyCode::KEY_A,
        "KEY_S", KeyCode::KEY_S,
        "KEY_D", KeyCode::KEY_D,
        "KEY_ESCAPE", KeyCode::KEY_ESCAPE
        // Thêm các key khác nếu cần
    );
    lua.new_enum("MouseButton",
        "BUTTON_LEFT", MouseButton::BUTTON_LEFT,
        "BUTTON_RIGHT", MouseButton::BUTTON_RIGHT
        // Thêm các button khác nếu cần
    );
}

void LuaSystem::executeScript(const std::string& scriptPath) {
    try {
        lua.script_file(scriptPath);
    } catch (const sol::error& e) {
        std::cerr << "Lua error: " << e.what() << std::endl;
    }
}

} // namespace PhysX 