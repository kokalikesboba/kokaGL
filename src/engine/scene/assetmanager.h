#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "nlohmann/json.hpp"

#include "opengl/resources/shader.h"
#include "engine/runtime/texturepool.h"
#include "engine/scene/model.h"
#include "engine/scene/gizmo.h"

#include <fstream>
#include <memory>
#include <vector>

struct Entry {
    std::string name;
    std::unique_ptr<Model> modelPtr;
};

class AssetManager {
public:
    AssetManager(const std::string& manifestDir);
    void Reload();
    void SaveCurrentArrangement(); 
    std::vector<std::unique_ptr<Model>>* getModelList();
    std::vector<std::unique_ptr<Gizmo>>* getGizmoList();
    void Draw(Shader& mesh_shader, Shader& billboard_shader);
    ~AssetManager();
private:
    nlohmann::ordered_json source;

    std::string manifestDir;
    std::string modelDir;
    std::string imgDir;

    TexturePool texturepool;
    std::vector<std::unique_ptr<Model>> models;
    std::vector<std::unique_ptr<Gizmo>> gizmos;
};

#endif