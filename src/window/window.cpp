#include "window.h"

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
    this->width = width; 
    this->height = height;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowPtr = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!windowPtr) {
        throw std::runtime_error("Failed to create a GLFW window");
    }

    glfwSetWindowUserPointer(windowPtr, this);
    glfwSetFramebufferSizeCallback(windowPtr, FbSizeCallback);

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

void error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}