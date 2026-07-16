#ifndef SCENE_H
#define SCENE_H

#include "nlohmann/json.hpp"

#include "engine/runtime/texturepool.h"

#include "engine/scene/model.h"
#include "engine/scene/gizmo.h"
#include "engine/scene/light.h"
#include "engine/scene/camera.h"

#include <fstream>
#include <memory>
#include <vector>

struct Entry {
    std::string name;
    std::unique_ptr<Model> modelPtr;
};

class Scene {
public:
    Scene(const std::string& manifestDir);
    void Reload();
    void SaveCurrentArrangement();
    std::vector<std::unique_ptr<Camera>>* GetCameraList();
    std::vector<std::unique_ptr<Model>>* GetModelList();
    std::vector<std::unique_ptr<Gizmo>>* GetGizmoList();
    ~Scene();
private:
    std::string manifestDir;
    nlohmann::ordered_json source;

    std::string modelDir;
    std::string imgDir;

    TexturePool texturepool;
    std::vector<std::unique_ptr<Camera>> cameras;
    std::vector<std::unique_ptr<Model>> models;
    std::vector<std::unique_ptr<Gizmo>> gizmos;
};

#endif