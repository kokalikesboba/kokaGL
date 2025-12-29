#ifndef WINDOW_H
#define WINDOW_H

#include "GLFW/glfw3.h"
#include <iostream>
#include <stdexcept>

class GlfwContext {
    public:
    GlfwContext();
    ~GlfwContext();

    //TODO: make non-copyable 

};

class Window {
    public:
    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();

    GLFWwindow* windowPtr;
    void makeContextCurrent() const;
    void swapBuffers() const;
    void pollEvents() const;

    bool shouldClose() const;

    //TODO: make non-copyable 

};

#endif