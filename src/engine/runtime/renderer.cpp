#include "renderer.h"

Renderer::Renderer(const std::string& configDir, const Scene& scene) :
scene(&scene)
{
    std::ifstream file(configDir);
    if (!file.is_open()) {
        throw std::runtime_error("[FATAL][Renderer] can't open manifest: " + configDir);
    }
    source = nlohmann::ordered_json::parse(file);

    CreateShaders();
    CreateViewport();
    CreateMesh();
    LinkViewportUniformBlock();
}

void Renderer::DrawMesh(int fbWidth, int fbHeight)
{
    for (auto& v : viewports) {
        v->Resize(fbWidth, fbHeight);
        v->UpdateUniformBlock(
            scene->GetCameraList()[0]->GetCameraMatrix(fbWidth, fbHeight),
            scene->GetCameraList()[0]->GetRotationMatrix(),
            scene->GetCameraList()[0]->GetPosition()
        );
    }

    for (size_t i = 0; i < meshes.size(); ++i) {
        for (const auto& tex : meshTextures[i]) {
            tex->Bind(static_cast<GLuint>(tex->GetType().type));
        }
        meshes[i]->Draw(*shaders[0]);
    }
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
        meshes.emplace_back(
            std::make_unique<Mesh>(
                *m->GetVertices(),
                *m->GetIndices()
            )
        );

        // Resolve the model's parsed texture data into GPU textures,
        // deduplicated by content hash through the pool. Hash 0 (shame
        // texture) is pre-cached by the pool's constructor.
        const auto& texInfo = *m->GetTexInfo();
        const auto& texData = *m->GetTexData();

        std::vector<std::shared_ptr<Texture>> textures;
        textures.reserve(texInfo.size());
        for (size_t i = 0; i < texInfo.size(); ++i) {
            if (texturePool.isCachedAndAlive(texInfo[i].hash)) {
                textures.push_back(texturePool.Get(texInfo[i].hash));
            } else {
                textures.push_back(
                    texturePool.Add(
                        texInfo[i].hash,
                        texInfo[i].type,
                        texData[i],
                        texInfo[i].width,
                        texInfo[i].height
                    )
                );
            }
        }
        meshTextures.push_back(std::move(textures));
    }
}

void Renderer::LinkViewportUniformBlock()
{
    for (auto& v : this->viewports) {
        for (int i = 0; i < shaders.size(); ++i) {
            GLuint blockIndex = shaders[i]->GetUniformBlockIndex("viewportUBO");
            if (blockIndex != GL_INVALID_INDEX) {
                v->LinkUniformBlock(*shaders[i], blockIndex);
            }
        }
    }
}
