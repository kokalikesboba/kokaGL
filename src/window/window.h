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
   
    void MakeContextCurrent() const;
    void SwapBuffers() const;
    void PollEvents() const;
    void VerticalSync(bool state) const;
    void RenameWindow(const char* title) const;

    bool ShouldClose() const;
    GLFWwindow* GetWindowPtr() const;
    int GetWidth() const;
    int GetHeight()  const;
    int GetFbWidth() const;
    int GetFbHeight() const;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    ~Window();

private:
    GLFWwindow* windowPtr;

    int width = 800;
    int height = 600;
    int fbWidth = 800;
    int fbHeight = 600;
};

#endif      