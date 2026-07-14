#include "renderer.h"

Renderer::Renderer(std::string configDir, std::vector<std::unique_ptr<Model>> *models, std::vector<std::unique_ptr<Gizmo>> *gizmos) : 
models(models),
gizmos(gizmos) 
{
    std::ifstream file(configDir);
    if (!file.is_open()) {
        throw std::runtime_error("[FATAL][Renderer] can't open manifest: " + configDir);
    }
    auto source = nlohmann::ordered_json::parse(file);
    shaderDir = std::string(source.at("shaderDir"));
    for (const auto& entry : source.at("shaders")) {
        shaders.emplace_back(
            std::make_unique<Shader>(
                shaderDir + std::string(entry.at("name")) + std::string(".vert"),
                shaderDir + std::string(entry.at("name")) + std::string(".frag")
            )
        );
    }
}

Renderer::~Renderer()
{
}
