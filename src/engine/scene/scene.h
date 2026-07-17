#ifndef SCENE_H
#define SCENE_H

#include "nlohmann/json.hpp"

#include "engine/scene/camera.h"
#include "engine/scene/model.h"
#include "engine/scene/gizmo.h"
#include "engine/scene/light.h"

#include <fstream>
#include <memory>
#include <vector>

class Scene {
public:
    Scene(const std::string& manifestDir);
    void Reload();
    void SaveCurrentArrangement();
    const std::vector<std::unique_ptr<Camera>>& GetCameraList() const;
    const std::vector<std::unique_ptr<Model>>& GetModelList() const;
    const std::vector<std::unique_ptr<Gizmo>>& GetGizmoList() const;
    const std::vector<std::unique_ptr<Light>>& GetLightList() const;
    ~Scene();
private:
    void LoadCamera();
    void LoadModel();
    void LoadGizmos();

    std::string manifestDir;
    nlohmann::ordered_json source;
    std::string modelDir;
    std::string imgDir;

    std::vector<std::unique_ptr<Camera>> cameras;
    std::vector<std::unique_ptr<Model>> models;
    std::vector<std::unique_ptr<Gizmo>> gizmos;
    std::vector<std::unique_ptr<Light>> lights;

};

#endif