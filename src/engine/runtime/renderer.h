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
#include "engine/runtime/texturemap.h"

#include <utility>

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

struct MeshRenderInstance {
    const Model* owner;
    Shader* shader;
    size_t meshOffset;
    size_t textureGroupOffset;
    glm::mat4 localTransform;
};

struct BillboardRenderInstance {
    const Gizmo* owner;
    Shader* shader;
};

class Renderer {
public:
    Renderer(const std::string& configDir, const Scene& scene);
    void DrawModels();
    void DrawGizmo();
    void RebuildScene();
    void UpdateUniforms(int fbWidth, int fbHeight);
    ~Renderer();
protected:
    void ParseConfig(const std::string& configDir);

    void CreateShaders();
    void CreateViewport();
    void CreateMesh();
    void CreateBillboard();

    void LinkViewportUniformBlock();
    void LinkLightUniformBlock();

    void UpdateViewportUBO(int fbWidth, int fbHeight);
    void UpdateLightUBO();
    
    Shader& GetShaderByName(const std::string& name);
private:
    nlohmann::ordered_json source;
    const Scene* const scene;

    // Uniform blocks`
    UBO viewportBlock;
    UBO lightBlock;

    // Rendering resources
    std::vector<std::unique_ptr<Shader>> shaders;
    std::vector<std::unique_ptr<Viewport>> viewports;
    std::vector<std::unique_ptr<Framebuffer>> framebuffers;

    // Meshes
    std::vector<std::unique_ptr<Mesh>> meshes;
    TextureMap meshTextureMap;
    std::vector<std::vector<std::shared_ptr<Texture>>>  meshTextureGroups;
    std::vector<MeshRenderInstance> meshRenderQueue;

    // Billboards
    std::vector<std::unique_ptr<Billboard>> billboards;
    TextureMap billboardTextureMap;
    std::vector<std::shared_ptr<Texture>> billboardTextures;
    std::vector<BillboardRenderInstance> billboardRenderQueue;
};

#endif