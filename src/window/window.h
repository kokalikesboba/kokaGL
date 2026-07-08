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

    GlfwContext(const GlfwContext&) = delete;
    GlfwContext& operator=(const GlfwContext&) = delete;
};

class Window {
public:
    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();
   
    void MakeContextCurrent() const;
    void SwapBuffers() const;
    void PollEvents() const;
    void VerticalSync(bool state) const;
    void RenameWindow(const char* title) const;

    bool ShouldClose() const;
    int GetWidth() const;
    int GetHeight()  const;
    int GetFbWidth() const;
    int GetFbHeight() const;
    GLFWwindow* GetWindowPtr() const;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

private:
    GLFWwindow* windowPtr;

    int width = 800;
    int height = 600;
    int fbWidth = 800;
    int fbHeight = 600;
    std::string windowTitle;
    bool vSync = true;
};

#endif      