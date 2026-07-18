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

// Binding 1
struct lightUBO {
    glm::vec4 color0        = glm::vec4(0.f);
    glm::vec3 direction0    = glm::vec3(0.f);
    unsigned int pad0       = 0;
    glm::vec4 color1        = glm::vec4(0.f);
    glm::vec3 direction1    = glm::vec3(0.f);
    unsigned int pad1       = 0;
    glm::vec4 color2        = glm::vec4(0.f);
    glm::vec3 direction2    = glm::vec3(0.f);
    unsigned int pad2       = 0;
    glm::vec4 color3        = glm::vec4(0.f);
    glm::vec3 direction3    = glm::vec3(0.f);
    unsigned int pad3       = 0;
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
    void DrawModels(int fbWidth, int fbHeight);
    ~Renderer();
private:
    void CreateShaders();
    void CreateViewport();
    void CreateMesh();

    void LinkViewportUniformBlock();
    void LinkLightUniformBlock();

    const Scene* const scene;

    nlohmann::ordered_json source;
    std::string shaderDir;

    TexturePool texturePool;
    UBO viewportBlock;
    UBO lightBlock;

    std::vector<std::string> shaderNames;
    std::vector<std::unique_ptr<Shader>> shaders;
    std::vector<std::unique_ptr<Viewport>> viewports;
    std::vector<std::unique_ptr<Mesh>> meshes;
    std::vector<std::vector<std::shared_ptr<Texture>>> meshTextures;
    std::vector<std::unique_ptr<Gizmo>> gizmos;
};

#endif