#ifndef RENDERER_H
#define RENDERER_H

#include "nlohmann/json.hpp"

#include "opengl/buffers/ubo.h"
#include "opengl/resources/shader.h"
#include "opengl/resources/viewport.h"
#include "opengl/drawable/mesh.h"
#include "opengl/drawable/billboard.h"
#include "opengl/drawable/framebuffer.h"

#include "engine/scene/scene.h"
#include "engine/runtime/texturepool.h"

// Binding 0
struct viewportUBO {
	glm::mat4 matrix;
	glm::mat4 orientation;
	glm::vec3 pos;
	float pad0;
};

    struct Light {
    glm::vec4 color     = glm::vec4(0.f);
    glm::vec3 position  = glm::vec3(0.f);
    unsigned int pad    = 0;
    glm::vec3 direction = glm::vec3(0.f);
    unsigned int type   = 0;
};

// Binding 1
struct lightUBO {
    Light lights[4];
};

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
    //void DrawModels();
    void DrawGizmo();
    void UpdateUniforms(int fbWidth, int fbHeight);
    ~Renderer();
private:
    void CreateShaders();
    void CreateViewport();
    //void CreateMesh();
    void CreateGizmo();

    void LinkViewportUniformBlock();
    void LinkLightUniformBlock();

    void UpdateViewportUBO(int fbWidth, int fbHeight);
    void UpdateLightUBO();

    const Scene* const scene;

    nlohmann::ordered_json source;
    std::string shaderDir;

    UBO viewportBlock;
    UBO lightBlock;

    std::vector<std::string> shaderNames;
    std::vector<std::unique_ptr<Shader>> shaders;
    std::vector<std::unique_ptr<Viewport>> viewports;

    TexturePool texturePool;
    std::vector<std::shared_ptr<Texture>> textures;

    std::vector<std::unique_ptr<Mesh>> meshes;
    std::vector<std::unique_ptr<Billboard>> billboards;


};

#endif