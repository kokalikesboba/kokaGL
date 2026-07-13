#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "nlohmann/json.hpp"

#include "opengl/resources/shader.h"
#include "engine/runtime/texturepool.h"
#include "engine/scene/model.h"

#include <fstream>
#include <memory>
#include <vector>

struct Entry {
    std::string name;
    std::unique_ptr<Model> modelPtr;
};

class AssetManager {
public:
    AssetManager(const std::string& manifestDir, TexturePool& texturePool);
    void Reload();
    void SaveCurrentArrangement();
    // void Add();
    // void Remove();
    void Draw(Shader& shader);
    ~AssetManager();
private:
    std::string manifestDir;
    TexturePool* const texturePool;
    std::vector<std::unique_ptr<Model>> queue;
    nlohmann::ordered_json source;
};

#endif