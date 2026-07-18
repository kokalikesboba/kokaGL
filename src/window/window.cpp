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

Window::Window(unsigned int width, unsigned int height, const char *title, bool gl_debug_context)
{
    this->width = width; 
    this->height = height;

    glfwSetErrorCallback(error_callback);
    if (gl_debug_context) {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    } else {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
    }

    // TODO: Thank you Apple for abandoning OpenGL right before it was finished.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowPtr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!windowPtr) {
        throw std::runtime_error("Failed to create a GLFW window");
    }

    glfwSetWindowSizeLimits(windowPtr, minWidth, minHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowUserPointer(windowPtr, this);
    glfwSetFramebufferSizeCallback(windowPtr, FbSizeCallback);
    glfwSetScrollCallback(windowPtr, ScrollCallback);

    // This is an icon loader, only works with Linux on X11 and Windows. 
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

    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);

}

void Window::MakeContextCurrent() const
{   
    glfwMakeContextCurrent(windowPtr);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(windowPtr);
}

void Window::PollEvents()
{
    glfwPollEvents();
    glfwGetWindowSize(windowPtr, &this->width, &this->height);
    glfwGetFramebufferSize(windowPtr, &this->fbWidth, &this->fbHeight);
}

void Window::RenameWindow(const char* title) const
{
    glfwSetWindowTitle(windowPtr, title);
}

void Window::EnableFullscreen() const
{
    glfwSetWindowMonitor(windowPtr, monitor, 0, 0, width, height, GLFW_DONT_CARE); 
}

void Window::DisableFullscreen() const
{
    glfwSetWindowMonitor(windowPtr, NULL, 0, 0, width, height, GLFW_DONT_CARE); 
}

void Window::VerticalSync(bool state) const
{
    glfwSwapInterval(state);
}

GLFWwindow *Window::GetWindowPtr() const
{
    // Constructor already checks if windowPtr is NULL
    return windowPtr;
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(windowPtr) != 0;
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

Window::~Window()
{
    if (windowPtr) {
        glfwDestroyWindow(windowPtr);
        windowPtr = nullptr;
    }
}

void Window::FbSizeCallback(GLFWwindow *win, int w, int h)
{
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(win));
    self->fbWidth = w;
    self->fbHeight = h;
}

void Window::ScrollCallback(GLFWwindow *win, double x, double y)
{
    Window* self = static_cast<Window*>(glfwGetWindowUserPointer(win));
    self->scrollX += x;
    self->scrollY += y;
}

void Window::ConsumeScroll(double& x, double& y)
{
    x = scrollX;
    y = scrollY;
    scrollX = 0.0;
    scrollY = 0.0;
}