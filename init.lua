-- init.lua
-- Script khởi tạo cho PhysX Engine

print("Hello from Lua script!")

-- Tạo một entity mới
local myEntity = create_entity()
myEntity:add_rigidbody(10.0) -- Thêm RigidBody component với khối lượng 10kg
myEntity:set_position(Vector3(0, 5, 0)) -- Đặt vị trí ban đầu
myEntity:add_mesh_renderer("default_cube", "default_material") -- Thêm MeshRenderer

-- Hàm update được gọi mỗi frame
function update(deltaTime)
    -- Áp dụng lực trọng trường
    myEntity:apply_force(Vector3(0, -9.8 * 10, 0))
    
    -- Kiểm tra input
    if Input:is_key_pressed(KeyCode.KEY_W) then
        print("W key pressed!")
    end
end 