#include "opengl/defaultcube.h"
#include "opengl/renderer/mesh.h"

#include "entities/model.h"

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

	// Create and link the shader program from source file6s
    Shader defaultShader("assets/shaders/default.vert", "assets/shaders/default.frag");

	Model cube("assets/models/cube");
	Model laika("assets/models/laika");
	Model sword("assets/models/sword");
	Model plane("assets/models/woodPlane");

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

		viewport.linkCameraPos(defaultShader, "camPos");

    	viewport.linkCameraMatrix(defaultShader, "camMatrix");

		cube.Draw(defaultShader);
		laika.Draw(defaultShader);
		sword.Draw(defaultShader);
		plane.Draw(defaultShader);

		window.measureTitleBarFPS(true);
		window.swapBuffers();
		window.measureTitleBarFPS(false);

	}

    // Manually release OpenGL resources
    defaultShader.Delete();

    return 0;
}
