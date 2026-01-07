#include "opengl/model.h"

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
	// One time global parameters
	glEnable(GL_DEPTH_TEST);

	// Create and link the shader program from source files
    Shader shaderProgram("assets/shaders/default.vert", "assets/shaders/default.frag");
	Shader lightShader("assets/shaders/light.vert", "assets/shaders/light.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	Camera camera(window.getWidth(), window.getHeight(), glm::vec3(0.f,0.f,3.f));

    // Main render loop
	while (!window.shouldClose())
	{
		window.pollEvents();



		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		// TODO: Decouple input management from camera class.
		camera.Inputs(window.getWindowPtr());
		camera.updateMatrix(45.f, 0.1f, 100.0f);
		


		window.measureTitleBarFPS(true);
		window.swapBuffers();
		window.measureTitleBarFPS(false);
	}

    // Manually release OpenGL resources
    shaderProgram.Delete();
	lightShader.Delete();

    return 0;
}
