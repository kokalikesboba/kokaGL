#ifndef WINDOW_H
#define WINDOW_H

#include "GLFW/glfw3.h"
#include <iostream>
#include <stdexcept>
#include <chrono>

class GlfwContext {
    public:
    GlfwContext();
    ~GlfwContext();
    //TODO: make non-copyable 
};

class Window {
public:
    // Constructor / Destructor
    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();
   
    // Crucial functions
    void makeContextCurrent() const;
    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;

    // Getters
    float getWidth();
    float getHeight();
    GLFWwindow* getWindowPtr();

    // Fun operators to play around with
    void verticalSync(bool state) const;
    // TODO: Not ideal but fine for now
    void measureTitleBarFPS(bool state);

    // TODO: I implemented this without a clear understanding between the canvas size and viewport size. This needs to be redone with a better understanding.
    void resizeViewport() const;

private:

    // TODO: Make windowPtr non-copyable. 
    GLFWwindow* windowPtr;
    std::string desiredTitle;

    // FPS related
    std::chrono::time_point<std::chrono::high_resolution_clock> frameTimeStart;
    std::chrono::time_point<std::chrono::high_resolution_clock> frameTimeEnd;
    void renameWindow(const char* title) const;

};

#endif