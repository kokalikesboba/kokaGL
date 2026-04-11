#ifndef WINDOW_H
#define WINDOW_H

#include "GLFW/glfw3.h"
#include "stb/stb_img.h"

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
    // Constructor / Destructor
    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();
   
    // Crucial functions
    void makeContextCurrent() const;
    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;

    // Getters
    int getWidth();
    int getHeight();
    int getFbWidth();
    int getFbHeight();
    GLFWwindow* getWindowPtr();

    // Fun stuff
    void verticalSync(bool state) const;
    void renameWindow(const char* title) const;

private:

    // TODO: Make windowPtr non-copyable.
    GLFWwindow* windowPtr;

    int width = 100;
    int height = 100;
    int fbWidth = 100;
    int fbHeight = 100;
    std::string windowTitle;
    bool vSync = true;
};

#endif      