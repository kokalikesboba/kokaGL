#include "window.h"

GlfwContext::GlfwContext()
{
    // Initialize GLFW library
    if (!glfwInit()) {
        throw std::runtime_error("Failed to init GLFW");
    }
}

GlfwContext::~GlfwContext()
{
    // Shut down GLFW and destroy the window/context
    glfwTerminate();
}

Window::Window(unsigned int width, unsigned int height, const char *title) 
{
    windowPtr = nullptr;

    // Request an OpenGL 3.3 core profile context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window and associated OpenGL context
    windowPtr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!windowPtr) {
        throw std::runtime_error("Failed to create a GLFW window");
    }

    glfwMakeContextCurrent(windowPtr);
}

Window::~Window()
{
    if (windowPtr) {
        glfwDestroyWindow(windowPtr);
        windowPtr = nullptr;
    }
}

void Window::makeContextCurrent() const
{
    glfwMakeContextCurrent(windowPtr);
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(windowPtr);
}

void Window::pollEvents() const
{
    glfwPollEvents();

    if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(windowPtr, GLFW_TRUE);
    }
}


bool Window::shouldClose() const
{
    return glfwWindowShouldClose(windowPtr) != 0;
}