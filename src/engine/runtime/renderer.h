#ifndef RENDERER_H
#define RENDERER_H

#include "nlohmann/json.hpp"

#include "engine/scene/scene.h"
#include "engine/runtime/texturepool.h"

#include "opengl/resources/viewport.h"
#include "opengl/resources/shader.h"
#include "opengl/drawable/mesh.h"
#include "opengl/drawable/billboard.h"
#include "opengl/drawable/framebuffer.h"

enum class DrawMode {
    Default,
    Mesh,
    Gizmo,
    Framebuffer,
    Mesh_On_Top
};

class Renderer {
public:
    Renderer(const std::string& configDir, const Scene& scene);
    void DrawModels(int fbWidth, int fbHeight);
    ~Renderer();
private:
    void CreateShaders();
    void CreateViewport();
    void CreateMesh();

    void LinkViewportUniformBlock();

    const Scene* const scene;

    nlohmann::ordered_json source;
    std::string shaderDir;

    TexturePool texturePool;

    std::vector<std::string> shaderNames;
    std::vector<std::unique_ptr<Shader>> shaders;
    std::vector<std::unique_ptr<Viewport>> viewports;

    std::vector<std::unique_ptr<Mesh>> meshes;
    std::vector<std::vector<std::shared_ptr<Texture>>> meshTextures;
    std::vector<std::unique_ptr<Gizmo>> gizmos;
};

#endif