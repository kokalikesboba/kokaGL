#include "renderer.h"

Renderer::Renderer(const std::string& configDir, const Scene& scene) :
scene(&scene),
viewportBlock(sizeof(viewportUBO), 0),
lightBlock(sizeof(lightUBO), 1)
{
    std::ifstream file(configDir);
    if (!file.is_open()) {
        throw std::runtime_error("[FATAL][Renderer] can't open manifest: " + configDir);
    }
    source = nlohmann::ordered_json::parse(file);

    CreateShaders();
    CreateViewport();
    CreateMesh();
    CreateGizmo();
    
    LinkViewportUniformBlock();
    LinkLightUniformBlock();    
}

void Renderer::DrawModels()
{
    Shader& shader = GetShaderByName("mesh_phong");
    for (const auto& entry : meshes) {
        // TexType doubles as the texture unit (BaseColor -> 0, etc.),
        // which matches the sampler defaults in the shaders.
        for (const auto& tex : entry.textures) {
            tex->Bind(static_cast<GLuint>(tex->GetType().type));
        }

        entry.mesh->Draw(
            shader,
            entry.model->GetPosition(),
            entry.model->GetOrientation(),
            entry.model->GetScale()
        );
    }
}

void Renderer::DrawGizmo()
{
    Shader& shader = GetShaderByName("bb_default");
    for (const auto& entry : billboards) {
        entry.texture->Bind(static_cast<GLuint>(entry.texture->GetType().type));

        entry.billboard->Draw(
            shader,
            entry.gizmo->GetPosition(),
            glm::vec2({1, 1})
        );
    }
}

void Renderer::RebuildScene()
{
    meshes.clear();
    billboards.clear();
    CreateMesh();
    CreateGizmo();
}

void Renderer::UpdateUniforms(int fbWidth, int fbHeight)
{
    // TODO: To reiterate, only the targets the first camera in a scene.
    UpdateViewportUBO(fbWidth, fbHeight);
    UpdateLightUBO();
}

Renderer::~Renderer()
{}

void Renderer::CreateShaders()
{
    shaderDir = std::string(source.at("shaderDir"));
    for (const auto& entry : source.at("shaders")) {
        shaderNames.emplace_back(entry.at("name"));
        shaders.emplace_back(
            std::make_unique<Shader>(
                shaderDir + std::string(entry.at("name")) + std::string(".vert"),
                shaderDir + std::string(entry.at("name")) + std::string(".frag")
            )
        );
    }
}

void Renderer::CreateViewport()
{
    for (const auto& c : scene->GetCameraList()) {
        viewports.emplace_back(std::make_unique<Viewport>());
    }
}

void Renderer::CreateMesh()
{
    for (const auto& m : scene->GetModelList()) {
        for (const auto& renderData : *m->GetModelRenderData()) {
            MeshEntry entry;
            entry.model = m.get();
            entry.mesh = std::make_unique<Mesh>(
                renderData.vertices,
                renderData.indices
            );

            // Resolve each TextureData through the pool: duplicates dedupe
            // by hash, and the resulting shared_ptrs live with this entry.
            entry.textures.reserve(renderData.texData.size());
            for (const auto& td : renderData.texData) {
                entry.textures.push_back(texturePool.GetOrAdd(td));
            }

            meshes.push_back(std::move(entry));
        }
    }
}

void Renderer::CreateGizmo()
{
    for (const auto& g : scene->GetGizmoList()) {
        BillboardEntry entry;
        entry.gizmo = g.get();
        entry.billboard = std::make_unique<Billboard>();
        entry.texture = texturePool.GetOrAdd(*g->GetTexData());
        billboards.push_back(std::move(entry));
    }
}

Shader& Renderer::GetShaderByName(const std::string& name)
{
    for (size_t i = 0; i < shaderNames.size(); ++i) {
        if (shaderNames[i] == name) return *shaders[i];
    }
    std::cerr << "[ERROR][Renderer] Unknown shader requested: " << name << ", defaulting to: " << shaderNames[0] << std::endl;
    return *shaders[0];
}

void Renderer::LinkViewportUniformBlock()
{
    for (int i = 0; i < shaders.size(); ++i) {
        GLuint blockIndex = shaders[i]->GetUniformBlockIndex("viewportUBO");
        if (blockIndex != GL_INVALID_INDEX) {
            viewportBlock.LinkBlock(*shaders[i], blockIndex);
        }
    }
}

void Renderer::LinkLightUniformBlock()
{
    for (int i = 0; i < shaders.size(); ++i) {
        GLuint blockIndex = shaders[i]->GetUniformBlockIndex("lightUBO");
        if (blockIndex != GL_INVALID_INDEX) {
            lightBlock.LinkBlock(*shaders[i], blockIndex);
        }
    }
}

void Renderer::UpdateViewportUBO(int fbWidth, int fbHeight)
{
    for (auto& v : viewports) {
        v->Resize(fbWidth, fbHeight);
        viewportBlock.Update(viewportUBO{
            scene->GetCameraList()[0]->GetCameraMatrix(fbWidth, fbHeight),
            scene->GetCameraList()[0]->GetRotationMatrix(),
            scene->GetCameraList()[0]->GetPosition(),
            0.f
        });
    }
}

void Renderer::UpdateLightUBO()
{
    int i = 0;
    Light light[4];
    for (const auto& entry : scene->GetLampList()) {
        light[i] = {
            entry->GetColor(),
            entry->GetPosition(),
            0,
            entry->GetEulerRotation(),
            0
        };
        ++i;
    }
    lightBlock.Update(light);
    Light rb[4];
    lightBlock.Bind();
    glGetBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(rb), rb);
    // breakpoint here — does rb[0].direction say (0,1,0)?
}
