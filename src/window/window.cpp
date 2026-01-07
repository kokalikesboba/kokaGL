#include "window.h"
#include "stb/stb_img.h"

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
    desiredTitle = std::string(title);

    // Request an OpenGL 3.3 core profile context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Create window and associated OpenGL context
    windowPtr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!windowPtr) {
        throw std::runtime_error("Failed to create a GLFW window");
    }
    GLFWimage icon;
    unsigned char* imgPixels =
        stbi_load("assets/textures/boub.png",
                &icon.width,
                &icon.height,
                nullptr,
                4);
    icon.pixels = imgPixels;
    if (!icon.pixels) {
        throw std::runtime_error("Failed to load window icon");
    }
    glfwSetWindowIcon(windowPtr, 1, &icon);
    stbi_image_free(imgPixels);
}

Window::~Window()
{
    if (windowPtr) {
        glfwDestroyWindow(windowPtr);
        windowPtr = nullptr;
    }
}

float Window::getWidth()
{
    int width;
    if (windowPtr) {
        glfwGetWindowSize(windowPtr, &width, nullptr);
        return width;
    } else {
        throw std::runtime_error("windowPtr is null");
        return -1.f;
    }     
}

float Window::getHeight()
{
    int height;
    if (windowPtr) {
        glfwGetWindowSize(windowPtr, &height, nullptr);
        return height;
    } else {
        throw std::runtime_error("windowPtr is null");
        return -1.f;
    }  
}

GLFWwindow *Window::getWindowPtr()
{
    // Constructor already checks if windowPtr is NULL
    return windowPtr;
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

void Window::resizeViewport() const
{
    int width, height;
    glfwGetFramebufferSize(windowPtr, &width, &height);
    glViewport(0, 0, width, height);
}

void Window::renameWindow(const char* title) const
{
    glfwSetWindowTitle(windowPtr, title);
}

void Window::verticalSync(bool state) const
{
    glfwSwapInterval(state);
}

void Window::measureTitleBarFPS(bool state)
{
    using clock = std::chrono::high_resolution_clock;

    if (state == true) { 
        frameTimeStart = clock::now();
    } else {
        frameTimeEnd = clock::now();
		std::chrono::duration<float> elapsed = frameTimeEnd - frameTimeStart;
		frameTimeStart = frameTimeEnd;
		float fps = 1.f / elapsed.count();
		std::string secondsAsString = std::to_string(fps);
		std::string title = desiredTitle + std::string(" - ") + secondsAsString + std::string(" FPS");
		renameWindow(title.c_str());
    }
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(windowPtr) != 0;
}

