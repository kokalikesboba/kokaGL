#include "opengl/renderer/mesh.h"
#include "parsers/gltfAssimp.h"

std::vector<Vertex> defaultCubeVertices = {
    // Positions          // Normals           // Colors           // UVs
    // Front face
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

    // Back face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},

    // Top face
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},  {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},  {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

    // Bottom face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},

    // Right face
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},  {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f},  {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f},  {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},

    // Left face
    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
};
 std::vector<GLuint> defaultCubeIndices = {
    0, 1, 2, 2, 3, 0,       // Front
    4, 5, 6, 6, 7, 4,       // Back
    8, 9, 10, 10, 11, 8,    // Top
    12, 13, 14, 14, 15, 12, // Bottom
    16, 17, 18, 18, 19, 16, // Right
    20, 21, 22, 22, 23, 20  // Left
};

std::vector<Texture> defaultTexture;


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
	std::vector<Texture> textures;
	textures.reserve(1);
	textures.emplace_back(textureType::Diffuse, 0);
	textures[0].stbLoad("assets/models/laika/textures/LaikaDiffuse_baseColor.png");

	MeshData data = loadModelData("assets/models/sword");
	Mesh mesh(
		std::move(data.vertices),
		std::move(data.indices),
		std::move(textures)
	);

	Shader lightShader("assets/shaders/light.vert", "assets/shaders/light.frag");
	defaultTexture.emplace_back(textureType::Diffuse, 0);
	Mesh light(
		std::move(defaultCubeVertices),
		std::move(defaultCubeIndices),
		std::move(defaultTexture)
	);

    // Main render loop
	while (!window.shouldClose())
	{
		window.pollEvents();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		// TODO: Decouple input management from viewport class.
		viewport.Inputs(window.getWindowPtr());
		viewport.updateCameraMatrix(45.f, 0.1f, 100.0f);

		viewport.linkCameraPos(shaderProgram, "camPos");
    	viewport.linkCameraMatrix(shaderProgram, "camMatrix");

		light.Draw(
			shaderProgram
		);
		
		mesh.Draw(
			shaderProgram,
			{0.f, 0.f, 0.f},
			{1.f, 0.f, 0.f, 0.f},
			{1.f, 1.f, 1.f}
		);

		window.measureTitleBarFPS(true);
		window.swapBuffers();
		window.measureTitleBarFPS(false);
	}

    // Manually release OpenGL resources
    shaderProgram.Delete();

    return 0;
}
