#include "opengl/resources/viewport.h"

#include "window/window.h"

#include "engine/entities/light.h"

class Input {
    public:
        Input(GLFWwindow* windowPtr);
        void Update(Viewport& viewport, const float& dt, Light& light);

    private:
        GLFWwindow* windowPtr;
        float movementSpeed = 10.f;
};