#include "window/window.h"

#include "engine/scene/scene.h"

#include <deque>
#include <utility>

class Input {
public:
    Input(Window& window);
    void Update(Camera& camera, const float dt);
protected:
    void HandleMouseInput(Camera& camera, const float dt);
    void HandleKeyboardInput(Camera& camera, const float dt);
private:
    Window& window;

    float movementSpeed = 10.f;
    double mouseSensitivity = 0.001f;
    double trackpadSensitivity = 0.025f;

    glm::dvec2 cursorPos;
    std::deque<glm::dvec2>cursorHistory;
    size_t maxHistory = 2;
    bool firstClick = true;
};