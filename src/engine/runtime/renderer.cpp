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
}

void Renderer::DrawMesh(int fbWidth, int fbHeight)
{

    LinkViewportUniformBlock();

    for (auto& v : viewports) {
        v->Resize(fbWidth, fbHeight);
        v->UpdateUniformBlock(
            scene->GetCameraList()[0]->GetCameraMatrix(fbWidth, fbHeight),
            scene->GetCameraList()[0]->GetRotationMatrix(),
            scene->GetCameraList()[0]->GetPosition()
        );
    }

    for (auto& m : meshes) {
        m->Draw(*shaders[0]);
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
                m->GetVertices(),
                m->GetIndices()
            )
        );
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


/*
for (int i = 0; i < parsed.texHash.size(); ++i) {
    if (textureCache->isCachedAndAlive(parsed.texHash[i])) {
        textures.push_back(textureCache->Get(parsed.texHash[i]));
    } else {
        textures.push_back(
            textureCache->Add(
                parsed.texHash[i],
                parsed.texType[i],
                parsed.texData[i],
                parsed.texWidth[i],
                parsed.texHeight[i]
            )
        );
    }
}
*/