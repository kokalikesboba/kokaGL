#ifndef RENDERINTERFACE_H
#define RENDERINTERFACE_H

#include "engine/scene/scene.h"

// I am not familiar with Vulkan, so I am using OGL paradigms
class RenderInterface {
public:
    // Pass read only reference to Renderer
    void AssignScene(const Scene& const scene);
    void DrawModels();
    void ReloadModels();
private:
    void AllocateModels();
};

#endif