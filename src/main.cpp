#include "opengl/mesh.h"

// Define the 4 corners of a square
std::vector<Vertex> vertices = {
    // Position             // Normal (Up)         // Color (White)      // UVs
    {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0,0,1), glm::vec3(1,1,1), glm::vec2(0,0)}, // Bottom Left
    {glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0,0,1), glm::vec3(1,1,1), glm::vec2(1,0)}, // Bottom Right
    {glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0,0,1), glm::vec3(1,1,1), glm::vec2(1,1)}, // Top Right
    {glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0,0,1), glm::vec3(1,1,1), glm::vec2(0,1)}  // Top Left
};

// Indices to form two triangles from the 4 vertices
std::vector<GLuint> indices = {
    0, 1, 2, // First Triangle
    0, 2, 3  // Second Triangle
};

int main()
{ 
    GlfwContext glfw;
    Window window(800, 800 , "kokaGL");
    window.makeContextCurrent();

    // Load OpenGL function pointers via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }
	// One time global parameters
	glEnable(GL_DEPTH_TEST);

	Viewport viewport(window.getWidth(), window.getHeight(), glm::vec3(0.f,0.f,-2.f));

	// Create and link the shader program from source files
    Shader shaderProgram("assets/shaders/default.vert", "assets/shaders/default.frag");
	shaderProgram.Activate();

	Texture boub(textureType::Diffuse, 0);
	boub.stbLoad("assets/images/pixelvap.png");
	boub.genTexture();
	boub.linkUni(shaderProgram,"diffuse0");
	std::vector<Texture> textures;
	textures.push_back(boub);

	Mesh mesh(vertices, indices, textures);

    // Main render loop
	while (!window.shouldClose())
	{
		window.pollEvents();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		// TODO: Decouple input management from viewport class.
		viewport.Inputs(window.getWindowPtr());
		viewport.updateMatrix(45.f, 0.1f, 100.0f);



		window.measureTitleBarFPS(true);
		window.swapBuffers();
		window.measureTitleBarFPS(false);
	}

    // Manually release OpenGL resources
    shaderProgram.Delete();

    return 0;
}
