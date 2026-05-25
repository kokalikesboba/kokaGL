#include "opengl/resources/viewport.h"

#include "window/window.h"

#include "engine/entities/light.h"

#include <deque>
#include <utility>

class Input {
    public:
        Input(GLFWwindow* windowPtr);
        void Update(Viewport& viewport, const float& dt, Light& light);
    private:
        GLFWwindow* windowPtr;

        float movementSpeed = 10.f;
        double sensitivity = 0.001f; 

        glm::dvec2 cursorPos = {0.f, 0.f};
        std::deque<glm::dvec2>cursorHistory;
        size_t maxHistory = 2;
        bool firstClick = true;

        bool trackpadMode = false;
        double trackpadSensitivity = 0.025f;
        double scrollX = 0.f;
        double scrollY = 0.f;
};