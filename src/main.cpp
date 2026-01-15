#include "opengl/renderer/mesh.h"
#include "parsers/gltfAssimp.h"
#include "opengl/buffers/ubo.h"

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
	textures.reserve(2);
	textures.emplace_back(textureType::Diffuse, 0);
	textures[0].stbLoad("assets/models/laika/textures/LaikaDiffuse_baseColor.png");
	textures.emplace_back(textureType::Specular, 1);
	textures[1].stbLoad("assets/speculars/spec.png");

	MeshData data = loadModelData("assets/models/sword/scene.gltf");
	Mesh mesh(
		std::move(data.vertices),
		std::move(data.indices),
		std::move(textures)
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
		viewport.updateMatrix(45.f, 0.1f, 100.0f);

		mesh.Draw(shaderProgram, viewport);

		window.measureTitleBarFPS(true);
		window.swapBuffers();
		window.measureTitleBarFPS(false);
	}

    // Manually release OpenGL resources
    shaderProgram.Delete();

    return 0;
}
