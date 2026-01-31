#include "entities/model.h"
#include "entities/light.h"

int main() {
	
    GlfwContext glfw;
    Window window(1000, 1000, "kokaGL");
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
	Model sphere("assets/models/sphere");

	Light light({1.f,1.f,1.f});

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

    	viewport.linkCameraMatrix(defaultShader, "cameraMatrix");
		viewport.linkCameraPos(defaultShader, "cameraPos");

		cube.Draw(defaultShader);
		laika.Draw(defaultShader);
		sword.Draw(defaultShader);
		plane.Draw(defaultShader);
		sphere.Draw(defaultShader);

		light.DrawGizmo(defaultShader);

		if (glfwGetKey(window.getWindowPtr(), GLFW_KEY_I) == GLFW_PRESS) {
			light.gizmo.Translate({0.f, 0.1f, 0.f});
		}
		if (glfwGetKey(window.getWindowPtr(), GLFW_KEY_K) == GLFW_PRESS) {
			light.gizmo.Translate({0.f, -0.1f, 0.f});
		}
		if (glfwGetKey(window.getWindowPtr(), GLFW_KEY_J) == GLFW_PRESS) {
			light.gizmo.Translate({-0.1f, 0.f, 0.0f});
		}
		if (glfwGetKey(window.getWindowPtr(), GLFW_KEY_L) == GLFW_PRESS) {
			light.gizmo.Translate({0.1f, 0.f, 0.0f});
		}

		window.measureTitleBarFPS(true);
		window.swapBuffers();
		window.measureTitleBarFPS(false);
	}

    // Manually release OpenGL resources
    defaultShader.Delete();

    return 0;
}
