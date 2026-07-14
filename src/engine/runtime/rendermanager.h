#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "engine/runtime/texturepool.h"

enum class DrawMode {
    Default,
    BackfaceCull,
    Framebuffer
};

class RenderManager {
public:
    RenderManager();
    ~RenderManager();
private:
    TexturePool texturepool;

};

#endif