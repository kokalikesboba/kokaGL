#ifndef SCENE_H
#define SCENE_H

#include "nlohmann/json.hpp"

#include "engine/scene/camera.h"
#include "engine/scene/model.h"
#include "engine/scene/gizmo.h"
#include "engine/scene/lamp.h"

#include <fstream>
#include <memory>
#include <vector>

class Scene {
public:
    Scene(const std::string& manifestDir);
    void Reload();
    void SaveCurrentArrangement();
    const std::vector<std::unique_ptr<Camera>>& GetCameraList() const;
    const std::vector<std::unique_ptr<Lamp>>& GetLampList() const;
    const std::vector<std::unique_ptr<Model>>& GetModelList() const;
    const std::vector<std::unique_ptr<Gizmo>>& GetGizmoList() const;
    ~Scene();
private:
    // TODO: Only one cameras supported
    void LoadCameras();
    void LoadLamps();
    void LoadModels();
    void LoadGizmos();

    std::string manifestDir;
    nlohmann::ordered_json source;
    std::string modelDir;
    std::string imgDir;

    std::vector<std::unique_ptr<Camera>> cameras;
    std::vector<std::unique_ptr<Lamp>> lamps;
    std::vector<std::unique_ptr<Model>> models;
    std::vector<std::unique_ptr<Gizmo>> gizmos;
};

#endif