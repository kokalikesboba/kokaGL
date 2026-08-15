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
#include <thread>

class Scene {
public:
    Scene(const std::string& manifestDir, const bool verbose = false);
    void Reload();
    // TODO: Not finished.
    void SaveCurrentArrangement();
    void PurgeModels();

    void SetPrimaryCamera(int cameraIndex);
    Camera &GetPrimaryCamera();

    const std::vector<std::unique_ptr<Camera>>& GetCameraList() const;
    const std::vector<std::unique_ptr<Lamp>>& GetLampList() const;
    const std::vector<std::unique_ptr<Model>>& GetModelList() const;
    const std::vector<std::unique_ptr<Gizmo>>& GetGizmoList() const;
    ~Scene();
protected:
    // TODO: Only one cameras supported
    void LoadCameras();
    void LoadLamps();
    void LoadModels();
    void LoadGizmos();
private:
    const bool verbose;

    std::string manifestDir;
    nlohmann::ordered_json source;
    std::string modelDir;
    std::string imgDir;

    std::vector<std::unique_ptr<Camera>> cameras;
    std::vector<std::unique_ptr<Lamp>> lamps;
    std::vector<std::unique_ptr<Model>> models;
    std::vector<std::unique_ptr<Gizmo>> gizmos;

    int cameraIndex;
};

#endif