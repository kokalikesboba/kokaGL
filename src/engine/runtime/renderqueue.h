#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include "engine/scene/model.h"

#include <vector>

class RenderQueue {
public:
    RenderQueue();
    void Add();
    void Remove();
    void Draw();
    ~RenderQueue();
private:
    std::vector<Model> queue;
};

#endif