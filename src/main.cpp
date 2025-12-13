#include "utils.h"   // processInput, framebuffer_size_callback, loadFile, logs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>



int main()
{
    // 1) Init GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2) Create window + context
    GLFWwindow* window =
        glfwCreateWindow(800, 600, "kokaGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 3) Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 4) Triangle vertex data (positions only)
    float triangle[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };

    // 5) VAO + VBO
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                  // location = 0
        3,                  // vec3
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // 6) UBO (viewProj + color)
    float viewProj[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
    float color[4] = { 1, 1, 1, 1 };

    GLuint ubo;
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, 80, nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 64, viewProj);
    glBufferSubData(GL_UNIFORM_BUFFER, 64, 16, color);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // 7) Shaders
    std::string vsSrc = loadFile("src/shaders/vertex.glsl");
    std::string fsSrc = loadFile("src/shaders/fragment.glsl");

    const char* vsrc = vsSrc.c_str();
    const char* fsrc = fsSrc.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsrc, nullptr);
    glCompileShader(vs);
    printShaderLog(vs, "vertex");

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsrc, nullptr);
    glCompileShader(fs);
    printShaderLog(fs, "fragment");

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    printProgramLog(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    // Bind UBO block to binding point 0 (GLSL 330-safe)
    GLuint blockIndex = glGetUniformBlockIndex(program, "Globals");
    if (blockIndex != GL_INVALID_INDEX) {
        glUniformBlockBinding(program, blockIndex, 0);
    }

    // 8) Render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}