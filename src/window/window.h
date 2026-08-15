#ifndef WINDOW_H
#define WINDOW_H

// TODO: Until I have a proper build managers, both of these are gonna be compiled.
#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "engine/parsers/png.h"

#include <iostream>
#include <stdexcept>

class GlfwContext {
    public:
    GlfwContext();
    ~GlfwContext();

    GlfwContext(const GlfwContext&) = delete;
    GlfwContext& operator=(const GlfwContext&) = delete;
};

enum class GfxAPI {
    OpenGL,
    None
};

class Window {
public:
    Window(unsigned int width, unsigned int height, const char* title, GfxAPI api);

    void PollEvents();
    void ConsumeScroll(double& x, double& y);
    void VerticalSync(bool state) const;
    void RenameWindow(const char* title) const;
    void EnableFullscreen() const;
    void DisableFullscreen() const;

    GLFWwindow* GetWindowPtr() const;   
    
    bool ShouldClose() const;

    int GetWidth() const;
    int GetHeight()  const;
    int GetFbWidth() const;
    int GetFbHeight() const;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    ~Window();

// OpenGL related functions.
public:
    void MakeContextCurrent() const;
    void SwapBuffers() const;
protected:
    void OGLWindowHints() const;

// API Nuetral
protected:
    void NoneWindowHints() const;

private:
    GlfwContext glfw;
    GLFWmonitor* monitor = nullptr;
    const GLFWvidmode* mode = nullptr;
    GLFWwindow* windowPtr = nullptr;

    int width = 800;
    int height = 600;

    int minWidth = 320;
    int minHeight = 240;

    int fbWidth = 800;
    int fbHeight = 600;

    bool GL_DEBUG = true;

    // Scroll offsets accumulate across events between polls (trackpads can
    // fire several per frame), and reset on ConsumeScroll().
    double scrollX = 0.0;
    double scrollY = 0.0;

    static void FbSizeCallback(GLFWwindow* win, int w, int h);
    static void ScrollCallback(GLFWwindow* win, double x, double y);
};

#endif      