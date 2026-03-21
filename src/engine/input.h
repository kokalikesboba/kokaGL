#include "opengl/renderer/viewport.h"

#include "window/window.h"

#include "engine/entities/light.h"

class Input {
    public:
        Input(GLFWwindow* windowPtr);
        void Update(Viewport& viewport, Light& light);

    private:
        GLFWwindow* windowPtr;
};