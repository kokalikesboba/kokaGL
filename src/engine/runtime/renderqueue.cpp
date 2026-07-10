#include "renderqueue.h"

AssetManager::AssetManager(const std::string &manifestDir, TexturePool& texturePool) 
: 
manifestDir(manifestDir),
texturePool(&texturePool)
{
    Reload();
}

void AssetManager::Reload()
{
    std::ifstream file(manifestDir);
    if (!file.is_open())
        throw std::runtime_error("[AssetManager] can't open manifest: " + manifestDir);

    source = nlohmann::ordered_json::parse(file);
    queue.clear();
    for (const auto& entry : source.at("models")) {
        auto& m = queue.emplace_back(std::make_unique<Model>(
            entry.at("path").get<std::string>(), *texturePool));
        const auto& p = entry.at("position");
        const auto& r = entry.at("rotation");
        m->SetPosition({p[0], p[1], p[2]});
        m->SetEulerRotation({r[0], r[1], r[2]});
    }
}
void AssetManager::SaveCurrentArrangement()
{
    nlohmann::ordered_json data;
    data["models"] = nlohmann::ordered_json::array();

    const auto& srcModels = source.at("models");

    for (size_t i = 0; i < queue.size(); ++i) {
        nlohmann::ordered_json m = srcModels.at(i);
        glm::vec3 p = queue[i]->GetPosition();
        glm::vec3 r = queue[i]->GetEulerRotation();
        m["position"] = { p.x, p.y, p.z };
        m["rotation"] = { r.x, r.y, r.z };
        data["models"].push_back(std::move(m));
    }

    std::ofstream file(manifestDir);
    if (!file) throw std::runtime_error("[AssetManager] can't write manifest: " + manifestDir);
    file << data.dump(2);
}

void AssetManager::Draw(Shader& shader)
{
    for (auto& models : queue) {
        models->Draw(shader);
    }
}

AssetManager::~AssetManager()
{
}
