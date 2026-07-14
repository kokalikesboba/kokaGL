#include "rendermanager.h"

RenderManager::RenderManager(std::string configDir, std::vector<std::unique_ptr<Model>> *models, std::vector<std::unique_ptr<Gizmo>> *gizmos) : 
models(models),
gizmos(gizmos)
{
    auto source = nlohmann::ordered_json::parse(configDir);
    
    for (const auto& entry : source.at("viewport")) {
        ;
    }
}

void RenderManager::Draw(DrawMode)
{
}

RenderManager::~RenderManager()
{
}
