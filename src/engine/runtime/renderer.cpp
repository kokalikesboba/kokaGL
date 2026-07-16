#include "renderer.h"

Renderer::Renderer(std::string configDir, Scene& scene) : 
cameras(scene.GetCameraList()),
models(scene.GetModelList()),
gizmos(scene.GetGizmoList()) 
{
    std::ifstream file(configDir);
    if (!file.is_open()) {
        throw std::runtime_error("[FATAL][Renderer] can't open manifest: " + configDir);
    }
    auto source = nlohmann::ordered_json::parse(file);
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

    // Creates a GPU object for the Camera
    for (const auto& c : cameras) {
        viewports.emplace_back(std::make_unique<Viewport>());
    }

    // Linking every uniform block if applicable
    for (auto& v : viewports) {
        for (int i = 0; i < shaders.size(); ++i) {
            GLuint blockIndex = shaders[i]->GetUniformBlockIndex("viewportUBO");
            if (blockIndex != GL_INVALID_INDEX) {
                v->LinkUniformBlock(*shaders[i], blockIndex);
            }
        }
    }
}

void Renderer::Draw(int fbWidth, int fbHeight)
{
    for (auto& v : viewports) {
        v->Resize(fbWidth, fbHeight);
        v->UpdateUniformBlock(
            cameras[0]->GetCameraMatrix(fbWidth, fbHeight),
            cameras[0]->GetRotationMatrix(),
            cameras[0]->GetPosition()
        );
    }

    for (auto& m : models) {
        m->Draw(*shaders[0]);
    }
}   

Renderer::~Renderer()
{

}
