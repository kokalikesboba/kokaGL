#include "rendermanager.h"

RenderManager::RenderManager(std::string configDir, std::vector<std::unique_ptr<Model>> *models, std::vector<std::unique_ptr<Gizmo>> *gizmos) : 
models(models),
gizmos(gizmos)
{
    // std::string source = nlohmann::ordered_json::parse(configDir);
}

void RenderManager::Draw(DrawMode)
{
}

RenderManager::~RenderManager()
{
}
