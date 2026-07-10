#include "renderqueue.h"

RenderQueue::RenderQueue(const std::string &manifestDir, TexturePool& texturePool) 
: 
manifestDir(manifestDir),
texturePool(&texturePool)
{
    std::ifstream file(manifestDir);
    nlohmann::json data = nlohmann::json::parse(file);

    for (const auto& entry : data.at("models")) {
        auto n = std::string("name");
        auto& m = queue.emplace_back(std::make_unique<Model>(entry.at("path").get<std::string>(), *this->texturePool));
        const auto& p = entry.at("position");
        const auto& r = entry.at("rotation");
        m->SetPosition({p[0], p[1], p[2]});
        m->AddEulerRotation({r[0], r[1], r[2]});
    }
}

void RenderQueue::Reload()
{
    queue.clear();

    std::ifstream file(manifestDir);
    nlohmann::json data = nlohmann::json::parse(file);

    for (const auto& entry : data.at("models")) {
        auto n = std::string("name");
        auto& m = queue.emplace_back(std::make_unique<Model>(entry.at("path").get<std::string>(), *this->texturePool));
        const auto& p = entry.at("position");
        const auto& r = entry.at("rotation");
        m->SetPosition({p[0], p[1], p[2]});
        m->AddEulerRotation({r[0], r[1], r[2]});
    }
}

void RenderQueue::Draw(Shader& shader)
{
    for (auto& models : queue) {
        models->Draw(shader);
    }
}

RenderQueue::~RenderQueue()
{
}
