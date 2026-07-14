#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "nlohmann/json.hpp"

#include "engine/scene/model.h"
#include "engine/scene/gizmo.h"
#include "engine/runtime/texturepool.h"
#include "opengl/resources/viewport.h"

#include <vector>
#include <memory>
#include <string>

enum class DrawMode {
    Default,
    Mesh,
    Gizmo,
    Framebuffer,
    Mesh_On_Top
};

class RenderManager {
public:
    RenderManager(std::string configDir, std::vector<std::unique_ptr<Model>>* models, std::vector<std::unique_ptr<Gizmo>>* gizmos);
    void Draw(DrawMode);
    ~RenderManager();
private:
    std::string configDir;

    std::vector<std::unique_ptr<Shader>> shaders;
    
    std::vector<std::unique_ptr<Model>>* const models;
    std::vector<std::unique_ptr<Gizmo>>* const gizmos;
};

#endif