#ifndef RENDERER_H
#define RENDERER_H

#include "nlohmann/json.hpp"

#include "engine/scene/scene.h"
#include "engine/runtime/texturepool.h"
 
enum class DrawMode {
    Default,
    Mesh,
    Gizmo,
    Framebuffer,
    Mesh_On_Top
};

class Renderer {
public:
    Renderer(std::string configDir, Scene& scene);
    void UploadUniforms();
    ~Renderer();
private:
    std::string configDir;
    std::string shaderDir;

    std::vector<std::unique_ptr<Camera>>* const cameras;
    std::vector<std::unique_ptr<Model>>* const models;
    std::vector<std::unique_ptr<Gizmo>>* const gizmos;

    std::vector<std::string> shaderNames;
    std::vector<std::unique_ptr<Viewport>> viewports;
    std::vector<std::unique_ptr<Shader>> shaders;
};

#endif