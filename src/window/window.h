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
    float getWidth();
    float getHeight();
    GLFWwindow* getWindowPtr();

    void verticalSync(bool state) const;

    // TODO: I implemented this without a clear understanding between the canvas size and viewport size. This needs to be redone with a better understanding.
    void resizeViewport() const;

private:

    // TODO: Make windowPtr non-copyable. 
    GLFWwindow* windowPtr;
    std::string desiredTitle;
    bool vSync = true;


    void renameWindow(const char* title) const;

};

#endif      