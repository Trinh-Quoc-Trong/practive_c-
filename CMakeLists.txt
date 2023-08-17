cmake_minimum_required(VERSION 3.15)
project(PhysX-Engine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tùy chọn build
option(BUILD_WITH_VULKAN "Build with Vulkan support" ON)
option(BUILD_TESTS "Build unit tests" ON)

# Tìm GLFW và Vulkan
find_package(GLFW3 REQUIRED)
find_package(Vulkan REQUIRED COMPONENTS glslc)

# Thư viện bên thứ ba
include_directories(third_party)

# Include directories cho GLM (thường là header-only)
include_directories(third_party/glm)

# Add source files for collision, shader, input, mesh, asset_manager, particle
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# Engine chính
add_library(PhysX_Engine STATIC ${SRC_FILES})

# Liên kết các thư viện
target_link_libraries(PhysX_Engine
    GLFW::GLFW
    ${Vulkan_LIBRARIES}
    ${LUA_LIBRARIES}
)

# Ứng dụng demo
add_executable(PhysX_Demo src/main.cpp)
target_link_libraries(PhysX_Demo PhysX_Engine)

# Unit tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# Cài đặt
install(TARGETS PhysX_Engine DESTINATION lib)
install(DIRECTORY include/ DESTINATION include) 