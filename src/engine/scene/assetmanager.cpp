#include "assetmanager.h"

AssetManager::AssetManager(const std::string& manifestDir)
{
    this->manifestDir = manifestDir;
    Reload();
}

void AssetManager::Reload()
{
    models.clear();
    gizmos.clear();

    std::ifstream file(manifestDir);
    if (!file.is_open())
        throw std::runtime_error("[AssetManager] can't open manifest: " + manifestDir);

    source = nlohmann::ordered_json::parse(file);

    modelDir = source.at("modelDir");
    imgDir = source.at("imgDir");
    for (const auto& entry : source.at("models")) {
        auto& m = models.emplace_back(
            std::make_unique<Model> (
                modelDir + std::string(entry.at("name")),
                &this->texturepool  
            )
        );
        const auto& p = entry.at("position");
        const auto& r = entry.at("rotation");
        m->SetPosition({p[0], p[1], p[2]});
        m->SetEulerRotation({r[0], r[1], r[2]});
    }
    for (const auto& entry : source.at("gizmos")) {
        auto& g = gizmos.emplace_back(
            std::make_unique<Gizmo>(
                imgDir + std::string(entry.at("name"))
            )
        );
        const auto& p = entry.at("position");
        g->SetPosition({p[0], p[1], p[2]});
    }
}
void AssetManager::SaveCurrentArrangement()
{
    nlohmann::ordered_json data;

    data["modelDir"] = source.at("modelDir");
    data["imgDir"] = source.at("imgDir");
    data["models"] = nlohmann::ordered_json::array();
    data["gizmos"] = nlohmann::ordered_json::array();

    const auto& srcModels = source.at("models");
    for (size_t i = 0; i < models.size(); ++i) {
        nlohmann::ordered_json m = srcModels.at(i);
        glm::vec3 p = models[i]->GetPosition();
        glm::vec3 r = models[i]->GetEulerRotation();
        m["position"] = { p.x, p.y, p.z };
        m["rotation"] = { r.x, r.y, r.z };
        data["models"].push_back(std::move(m));
    }
    const auto& srcGizmos = source.at("gizmos");
    for(size_t i = 0; i < gizmos.size(); ++i) {
        nlohmann::ordered_json g = srcGizmos.at(i);
        glm::vec3 p = gizmos[i]->GetPosition();
        g["position"] = { p.x, p.y, p.z };
        data["gizmos"].push_back(std::move(g));
    }

    std::ofstream file(manifestDir);
    if (!file) throw std::runtime_error("[AssetManager] can't write manifest: " + manifestDir);
    file << data.dump(2);
}

std::vector<std::unique_ptr<Model>>* AssetManager::getModelList()
{
    return &models;
}

std::vector<std::unique_ptr<Gizmo>>* AssetManager::getGizmoList()
{
    return &gizmos;
}

void AssetManager::Draw(Shader& mesh_shader, Shader& billboard_shader)
{
    for (auto& models : models) {
        models->Draw(mesh_shader);
    }
    for (auto& gizmos : gizmos) {
        gizmos->Draw(billboard_shader);
    }
}

AssetManager::~AssetManager()
{
}
