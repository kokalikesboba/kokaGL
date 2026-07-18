#include "viewport.h"

Viewport::Viewport()
{
}

// Resizes viewport only if the window size has changed 
void Viewport::Resize(int width, int height)
{
    if ((prevWidth != width) || (prevHeight != height)) {
        prevWidth = width;
        prevHeight = height;
        glViewport(0,0, width, height);
    }
}

Viewport::~Viewport()
{
}
