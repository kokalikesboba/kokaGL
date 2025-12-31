
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "glfw/window.h"
#include "opengl/shader.h"
#include "opengl/vao.h"
#include "opengl/vbo.h"
#include "opengl/ebo.h"
#include "opengl/texture.h"
#include "opengl/camera.h"

#include <chrono>

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main()
{

    GlfwContext glfw;
    Window window(800, 800, "kokaGL");
    window.makeContextCurrent();

    // Load OpenGL function pointers via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

    // Create and link the shader program from source files
    Shader shaderProgram("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

	// VAO is explicitly bound because it is an input-state container.
	VAO VAO1;
	VAO1.Bind();
	// VB0/EBO are implicitly bound by their constructors for uploading data.
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Associate the VBO with the VAO and define vertex attribute layout
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbind objects to avoid accidental state modification
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

    Texture boub("assets/textures/boub.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    boub.texUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(window.getWidth(), window.getHeight(), glm::vec3(0.0f,0.0f,2.0f));

    // Main render loop
	while (!window.shouldClose())
	{	

		using clock = std::chrono::steady_clock;

		auto start = clock::now();

		// Clear the framebuffer with a solid background color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		// OpenGL will remember this state.
		shaderProgram.Activate();

		// TODO: Handles view and projection while uploading it as a uniform. It needs to be split into more member functions since it is too rigid.
		camera.uploadMatrixToUni(45.f, 0.1f, 100.f, shaderProgram, "camMatrix");

        boub.Bind();
        
        VAO1.Bind();

		// Draw indexed triangles using the element buffer
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		// Swap the front and back buffers
		window.swapBuffers();

		// Process pending window and input events
		window.pollEvents();

		// Resizes OpenGL's vieport to the size of the window.
		window.resizeViewport();

		// TODO: Decouple input management from camera class.
		camera.Inputs(window.windowPtr);

		auto end = clock::now();
		std::chrono::duration<float> elapsed = end - start;
		start = end;
		float fps = 1.f / elapsed.count();
		std::string secondsAsString = std::to_string(fps);
		std::string title = std::string("KokaGL - ") + secondsAsString + std::string(" FPS");
		window.renameWindow(title.c_str());

	}

    // Manually release OpenGL resources
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    return 0;
}
