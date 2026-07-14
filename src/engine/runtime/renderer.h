#ifndef RENDERER_H
#define RENDERER_H

#include "nlohmann/json.hpp"

#include "engine/scene/model.h"
#include "engine/scene/gizmo.h"
#include "engine/scene/light.h"
// Needs to be wrapped into a high level Camera
#include "opengl/resources/viewport.h"

#include "engine/runtime/texturepool.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <memory>

enum class DrawMode {
    Default,
    Mesh,
    Gizmo,
    Framebuffer,
    Mesh_On_Top
};

class Renderer {
public:
    Renderer(std::string configDir, std::vector<std::unique_ptr<Model>>* models, std::vector<std::unique_ptr<Gizmo>>* gizmos);
    void Draw(DrawMode);
    ~Renderer();
    // temporarily public
    std::vector<std::unique_ptr<Shader>> shaders;
private:
    std::string configDir;
    std::string shaderDir;


    // I should probably wrap this at some point
    // Viewport viewport;
    
    std::vector<std::unique_ptr<Model>>* const models;
    std::vector<std::unique_ptr<Gizmo>>* const gizmos;
    // std::vector<std::unique_ptr<Light>>* const lights;
};

#endif