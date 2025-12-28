#include "utils.h"   // framebuffer resize callback and other utilities

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "opengl/shader.h"
#include "opengl/vao.h"
#include "opengl/vbo.h"
#include "opengl/ebo.h"

#include <iostream>
#include <math.h>

// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

// Index buffer defining three triangles using the vertices above
GLuint indices[] = 
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

int main()
{
    // Initialize GLFW library
    if (!glfwInit()) {
        std::cerr << "Failed to init GLFW\n";
        return -1;
    }

    // Request an OpenGL 3.3 core profile context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window and associated OpenGL context
    GLFWwindow* window =
        glfwCreateWindow(800, 600, "kokaGL", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

    // Register callback to update the viewport when the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set the initial OpenGL viewport
	// Defines the region of the window OpenGL will render into
	glViewport(0, 0, 800, 800);

    // Create and link the shader program from source files
    Shader shaderProgram("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

	// Create a Vertex Array Object to store vertex attribute state
	VAO VAO1;
	VAO1.Bind();

	// Create a Vertex Buffer Object and upload vertex data to the GPU
	VBO VBO1(vertices, sizeof(vertices));

	// Create an Element Buffer Object and upload index data to the GPU
	EBO EBO1(indices, sizeof(indices));

	// Associate the VBO with the VAO and define vertex attribute layout
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Unbind objects to avoid accidental state modification
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Main render loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear the framebuffer with a solid background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate the shader program
		shaderProgram.Activate();
        glUniform1f(uniID, 0.5f);
		// Bind the VAO containing vertex and index state
		VAO1.Bind();

		// Draw indexed triangles using the element buffer
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap the front and back buffers
		glfwSwapBuffers(window);

		// Process pending window and input events
		glfwPollEvents();
	}

    // Manually release OpenGL resources
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    // Shut down GLFW and destroy the window/context
    glfwTerminate();
    return 0;
}
