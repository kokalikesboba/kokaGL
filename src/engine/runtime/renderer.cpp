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
    // CreateMesh();
    CreateGizmo();
    
    LinkViewportUniformBlock();
    LinkLightUniformBlock();    
}

/*
void Renderer::DrawModels()
{
    for (size_t i = 0; i < meshes.size(); ++i) {
        for (const auto& tex : meshTextures[i]) {
            tex->Bind(static_cast<GLuint>(tex->GetType().type));
        }

        // TODO: Needs multimesh loading, capped to first mesh
        meshes[i]->Draw(
            *shaders[0],
            scene->GetModelList()[i]->GetPosition(),
            scene->GetModelList()[i]->GetOrientation(),
            scene->GetModelList()[i]->GetScale()
        );
    }
}
*/
void Renderer::DrawGizmo()
{
    for (size_t i = 0; i < billboards.size(); ++i) {

        std::cout << scene->GetGizmoList()[i]->GetTexInfo()->hash << std::endl;

        billboards[i]->Draw(
            *shaders[0],
            scene->GetGizmoList()[i]->GetPosition(),
            glm::vec2({1, 1})
        );
    }
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

/*
void Renderer::CreateMesh()
{
    for (const auto& m : scene->GetModelList()) {
        meshes.emplace_back(std::make_unique<Mesh>(
            *m->GetVertices(),
            *m->GetIndices()
        ));

        std::vector<std::shared_ptr<Texture>> texs;
        const auto& texData = *m->GetTexInfo();   // vector of TextureData
        texs.reserve(texData.size());
        for (const auto& td : texData) {
            texs.push_back(texturePool.GetOrAdd(td));   // whole struct, one per slot
        }
        textures.push_back(texs);
    }
}*/

void Renderer::CreateGizmo()
{
    for (const auto& g : scene->GetGizmoList()) {
        billboards.emplace_back(
            std::make_unique<Billboard>()
        );

        textures.push_back(
            texturePool.GetOrAdd(*g->GetTexInfo())
        );
    }
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
