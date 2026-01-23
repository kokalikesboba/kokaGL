#include "opengl/defaultcube.h"
#include "opengl/renderer/mesh.h"
#include "parsers/gltfAssimp.h"

int main() {
	
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
    Shader defaultProgram("assets/shaders/default.vert", "assets/shaders/default.frag");

	returnedData parsed = loadModelData("assets/models/woodCube/woodCube.glb");

	std::vector<Texture> textures;
	textures.reserve(parsed.texTypeIndex.size());
	for (unsigned int i = 0; i < parsed.texTypeIndex.size(); ++i) {
		textures.emplace_back(parsed.texTypeIndex[i], i);
		std::string filename = parsed.texPath[i]; 
		std::string fullPath = "assets/models/woodCube/" + filename;
		
		textures[i].stbLoad(fullPath.c_str()); 
	}

	Mesh mesh(
		std::move(parsed.vertices),
		std::move(parsed.indices),
		std::move(textures)
	);

	Shader lightShader("assets/shaders/light.vert", "assets/shaders/light.frag");
	std::vector<Texture> defaultTexture;
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

		viewport.linkCameraPos(defaultProgram, "camPos");
    	viewport.linkCameraMatrix(defaultProgram, "camMatrix");

		light.Draw(
			lightShader
		);
		glUniform4f(glGetUniformLocation(lightShader.getID(), "lightColor"), 1.f, 0.f, 0.f, 1.f);

		mesh.Draw(
			defaultProgram,
			{0.f, 0.f, 0.f},
			{1.f, 0.f, 0.f, 0.f},
			{1.f, 1.f, 1.f}
		);

		window.measureTitleBarFPS(true);
		window.swapBuffers();
		window.measureTitleBarFPS(false);

	}

    // Manually release OpenGL resources
    defaultProgram.Delete();

    return 0;
}
