#include "window/window.h"

#include "engine/scene/scene.h"

#include <deque>
#include <utility>

class Input {
public:
    Input(Window& window);
    void Update(Camera& camera, const float dt);
private:
    Window& window;
    GLFWwindow* windowPtr = nullptr;

    float movementSpeed = 10.f;
    double sensitivity = 0.001f;

    glm::dvec2 cursorPos = {0.f, 0.f};
    std::deque<glm::dvec2>cursorHistory;
    size_t maxHistory = 2;
    bool firstClick = true;

    bool trackpadMode = false;
    double trackpadSensitivity = 0.025f;
};