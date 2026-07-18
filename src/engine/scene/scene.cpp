#include "scene.h"

Scene::Scene(const std::string& manifestDir)
{
    this->manifestDir = manifestDir;
    Reload();
}

void Scene::Reload()
{
    cameras.clear();
    lamps.clear();
    models.clear();
    gizmos.clear();

    std::ifstream file(manifestDir);
    if (!file.is_open())
        throw std::runtime_error("[Scene] can't open manifest: " + manifestDir);

    source = nlohmann::ordered_json::parse(file);
    modelDir = source.at("modelDir");
    imgDir = source.at("imgDir");

    LoadCameras();
    LoadLamps();
    LoadModels();
    LoadGizmos();
}
void Scene::SaveCurrentArrangement()
{
    nlohmann::ordered_json data;

    data["modelDir"] = source.at("modelDir");
    data["imgDir"] = source.at("imgDir");
    data["models"] = nlohmann::ordered_json::array();
    data["gizmos"] = nlohmann::ordered_json::array();

    // TODO: Pass through camera
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
    if (!file) throw std::runtime_error("[Scene] can't write manifest: " + manifestDir);
    file << data.dump(2);
}

const std::vector<std::unique_ptr<Camera>>& Scene::GetCameraList() const
{
    return cameras;
}

const std::vector<std::unique_ptr<Model>>& Scene::GetModelList() const
{
    return models;
}

const std::vector<std::unique_ptr<Gizmo>>& Scene::GetGizmoList() const
{
    return gizmos;
}

const std::vector<std::unique_ptr<Lamp>> &Scene::GetLampList() const
{
    return lamps;
}

Scene::~Scene()
{
}

void Scene::LoadCameras()
{
    for (const auto& entry : source.at("camera")) {
        cameras.emplace_back(std::make_unique<Camera>());
        auto& p = entry.at("position");
        auto& r = entry.at("rotation");
        cameras[0]->SetPosition({p[0], p[1], p[2]});
        cameras[0]->SetEulerRotation({r[0], r[1], r[2]});
    }
}

void Scene::LoadLamps()
{

    for (const auto& entry : source.at("lamps")) {
        auto& l = lamps.emplace_back(std::make_unique<Lamp>());
        auto& c = entry.at("color");
        auto& p = entry.at("position");
        auto& r = entry.at("rotation");
        auto& t = entry.at("type");
        l->SetColor({c[0], c[1], c[2], c[3]});
        l->SetPosition({p[0], p[1], p[2]});
        l->SetEulerRotation({r[0], r[1], r[2]});
        l->SetType(t);
    }
}

void Scene::LoadModels()
{
    for (const auto& entry : source.at("models")) {
        auto& m = models.emplace_back(
            std::make_unique<Model> (
                modelDir + std::string(entry.at("name"))
            )
        );
        const auto& p = entry.at("position");
        const auto& r = entry.at("rotation");
        m->SetPosition({p[0], p[1], p[2]});
        m->SetEulerRotation({r[0], r[1], r[2]});
    }
}

void Scene::LoadGizmos()
{
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
