#include "window.h"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

GlfwContext::GlfwContext()
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to init GLFW");
    }
}

GlfwContext::~GlfwContext()
{
    glfwTerminate();
}


Window::Window(unsigned int width, unsigned int height, const char *title) 
{
    windowPtr = nullptr;

    this->width = width; 
    this->height = height;
    windowTitle = std::string(title);

    // Request an OpenGL 3.3 core profile context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Create window and associated OpenGL context
    windowPtr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!windowPtr) {
        throw std::runtime_error("Failed to create a GLFW window");
    }
    glfwGetFramebufferSize(windowPtr, &this->fbWidth, &this->fbHeight);

    // glfwSetErrorCallback(error_callback);
    #if defined(__linux__) || defined(_WIN32)
        
        GLFWimage icon;
        unsigned char* imgPixels =
            stbi_load("assets/images/marz_boudle.png",
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
    #endif
}

Window::~Window()
{
    if (windowPtr) {
        glfwDestroyWindow(windowPtr);
        windowPtr = nullptr;
    }
}

int Window::GetWidth() const
{
    return width;
}

int Window::GetHeight() const
{
    return height;
}

int Window::GetFbWidth() const
{
    return fbWidth;
}

int Window::GetFbHeight() const
{
    return fbHeight;
}

GLFWwindow *Window::GetWindowPtr() const
{
    // Constructor already checks if windowPtr is NULL
    return windowPtr;
}

void Window::MakeContextCurrent() const
{
    glfwMakeContextCurrent(windowPtr);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(windowPtr);
}

void Window::PollEvents() const
{
    glfwPollEvents();
}

void Window::RenameWindow(const char* title) const
{
    glfwSetWindowTitle(windowPtr, title);
}

void Window::VerticalSync(bool state) const
{
    glfwSwapInterval(state);
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(windowPtr) != 0;
}

