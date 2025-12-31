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

   
    float getWidth();
    float getHeight();
    void makeContextCurrent() const;
    void swapBuffers() const;
    void pollEvents() const;
    void resizeViewport() const;
    void renameWindow(const char* title) const;
    void verticalSync(bool state) const;
    bool shouldClose() const;

    //TODO: make non-copyable 
    GLFWwindow* windowPtr;

};

#endif