#pragma once
#include <sol/sol.hpp>
#include "core/ecs.hpp"

namespace PhysX {

class LuaSystem {
public:
    LuaSystem();
    
    void bindEngineAPI(Scene& scene);
    void executeScript(const std::string& scriptPath);
    
private:
    sol::state lua;
};

} // namespace PhysX 