#ifndef WINDOW_H
#define WINDOW_H

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

    // Returns the pointer to the window 
    GLFWwindow* Get() const;   
    
    bool ShouldClose() const;

    int GetWidth() const;
    int GetHeight()  const;
    int GetCursorPosX() const;
    int GetCursorPosY() const;
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
    const GlfwContext glfw;
    GLFWmonitor* monitor = nullptr;
    const GLFWvidmode* mode = nullptr;
    GLFWwindow* windowPtr = nullptr;

    int minWidth = 320;
    int minHeight = 240;

    int width;
    int height;
    int fbWidth;
    int fbHeight;
    double cursorPosX;
    double cursorPosY;
    double scrollX;
    double scrollY;

    static void FbSizeCallback(GLFWwindow* win, int w, int h);
    static void ScrollCallback(GLFWwindow* win, double x, double y);
};

#endif      