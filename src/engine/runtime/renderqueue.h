#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

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

class RenderQueue {
public:
    RenderQueue(const std::string& manifestDir, TexturePool& texturePool);
    void Reload();
    // void Add();
    // void Remove();
    void Draw(Shader& shader);
    ~RenderQueue();
private:
    std::string manifestDir;
    TexturePool* const texturePool;
    std::vector<std::unique_ptr<Model>> queue;
};

#endif