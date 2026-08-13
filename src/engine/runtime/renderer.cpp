#include "renderer.h"

Renderer::Renderer(const std::string& configDir, const Scene& scene) :
scene(&scene),
viewportBlock(sizeof(viewportUBO), 0),
lightBlock(sizeof(lightUBO), 1)
{
    ParseConfig(configDir);
    CreateShaders();
    CreateViewport();
    CreateMesh();
    CreateBillboard();
    
    LinkViewportUniformBlock();
    LinkLightUniformBlock();    
}

void Renderer::Clear(glm::vec4 rgba)
{
    glClearColor(rgba.r, rgba.g, rgba.b, rgba.a);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawModels()
{
    for (auto& instance : meshRenderQueue) {
        for (const auto& texture : meshTextureGroups[instance.textureGroupOffset]) {
            texture->Bind(std::to_underlying(texture->GetType()));
        }

        auto worldMatrix = MatrixOps::TRSMatrix(
            instance.owner->GetPosition(),
            instance.owner->GetOrientation(),
            instance.owner->GetScale()
        );

        auto localMatrix = MatrixOps::TRSMatrix(
            instance.position,
            instance.orientation,
            instance.scale
        );

        auto modelMatrix = worldMatrix * localMatrix;
        
        meshes[instance.meshOffset]->Draw(
            *instance.shader,
            modelMatrix
        );
    }
}

void Renderer::DrawGizmo()
{
    Shader& shader = GetShaderByName("bb_default");
    for (size_t i = 0; i < billboards.size(); ++i) {
        billboardTextures[i]->Bind(std::to_underlying(billboardTextures[i]->GetType()));

        billboards[i]->Draw(
            shader,
            scene->GetGizmoList()[i]->GetPosition(),
            glm::vec2({1, 1})
        );
    }
}

void Renderer::RebuildScene()
{
    meshes.clear();
    billboards.clear();

    meshTextureGroups.clear();
    billboardTextures.clear();

    meshRenderQueue.clear();
    billboardRenderQueue.clear();

    CreateMesh();
    CreateBillboard();
}

void Renderer::UpdateUniforms(int fbWidth, int fbHeight)
{
    // TODO: To reiterate, only the targets the first camera in a scene.
    UpdateViewportUBO(fbWidth, fbHeight);
    UpdateLightUBO();
}

Renderer::~Renderer()
{}

void Renderer::ParseConfig(const std::string &configDir)
{
    std::ifstream file(configDir);
    if (!file.is_open()) {
        throw std::runtime_error("[FATAL][Renderer] can't open manifest: " + configDir);
    }
    source = nlohmann::ordered_json::parse(file);
}

void Renderer::CreateShaders()
{
    auto shaderDir = std::string(source.at("shaderDir"));

    if(source.find("mesh_fallback") == source.end())  {
        throw std::runtime_error("FATAL][Renderer] Please provide a fallback shader for mesh");
    } else {
        shaders.emplace_back(std::make_unique<Shader>(
            shaderDir + std::string(source.at("mesh_fallback")) + std::string(".vert"),
            shaderDir + std::string(source.at("mesh_fallback")) + std::string(".frag")
        ));
    };

    for (const auto& shaderEntry : source.at("shaders")) {
        // Create shaders
        auto shader = std::make_unique<Shader>(
            shaderDir + std::string(shaderEntry.at("name")) + std::string(".vert"),
            shaderDir + std::string(shaderEntry.at("name")) + std::string(".frag")
        );

        if (shaderEntry.find("texunits") == shaderEntry.end()) {
            std::cerr << "[WARNING][Renderer] No texture bindings specified for: " << shaderEntry.at("name") << "\n";
        } else {
            // Texture uniform bindings
            for (const auto& texEntry : shaderEntry.at("texunits")) {
                shader->UploadUni(std::string(texEntry.at("type")), int(texEntry.at("unit")));
            }
        }

        // Emplace back shader
        shaders.emplace_back(std::move(shader));
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
    for (const auto& model : scene->GetModelList()) {
        // for every mesh
        for (const auto& renderData : *model->GetRenderData()) {
            // push back into a mesh group's vertices and indices
            auto mesh = std::make_unique<Mesh> (
                renderData.vertices,
                renderData.indices
            );
            meshes.emplace_back(std::move(mesh));
            
            // create a group for each texture of a mesh.
            std::vector<std::shared_ptr<Texture>> textureGroup;
            for (const auto texture : renderData.texData) {
                // Run through deduplicator
                textureGroup.emplace_back(meshTextureMap.GetOrAdd(texture));
            }
            meshTextureGroups.emplace_back(std::move(textureGroup));

            MeshRenderInstance entry;
            entry.owner = &*model;
            // TODO: hardcoded to phong shader
            entry.shader = &GetShaderByName("mesh_phong");
            entry.meshOffset = meshes.size() - 1;
            entry.textureGroupOffset = meshTextureGroups.size() - 1;

            entry.position = renderData.position;
            entry.orientation = renderData.orientation;
            entry.scale = renderData.scale;

            meshRenderQueue.push_back(entry);
        }
    }
}

void Renderer::CreateBillboard()
{
    for (const auto& g : scene->GetGizmoList()) {
        billboardTextures.push_back(billboardTextureMap.GetOrAdd(*g->GetTexData()));
        billboards.emplace_back(std::make_unique<Billboard>());
    }
}

Shader& Renderer::GetShaderByName(const std::string& name)
{
    for (size_t i = 0; i < shaders.size(); ++i) {
        if (shaders[i]->GetName() == name) return *shaders[i];
    }
    std::cerr << "[ERROR][Renderer] Unknown shader requested: " << name << ", defaulting to: " << shaders[0] << std::endl;
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
    // TODO: yes i know this can overflow
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
}
