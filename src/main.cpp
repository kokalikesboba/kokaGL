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
	glEnable(GL_CULL_FACE);

	Viewport viewport(window.getWidth(), window.getHeight(), {-9.f,5.f,9.f}, {0.7f, -0.2f, -0.7f});

	// Create and link the shader program from source file6s
    Shader defaultShader("assets/shaders/default.vert", "assets/shaders/default.frag");
	Shader lightShader("assets/shaders/light.vert", "assets/shaders/light.frag");

	Model gridPlane("assets/models/gridPlane");
	gridPlane.SetPosition({0.f,0.f,0.f});

	Model sphere("assets/models/sphere");
	sphere.SetPosition({2.f,2.f,2.f});

	Model cubeStack("assets/models/cubeStack");
	cubeStack.SetPosition({-2.0f,0.1f,-2.0f});
	
	Model sword("assets/models/sword");
	sword.SetPosition({2.0f,1.f,-2.0f});

	Light light({1.f,1.f,1.f});
	light.SetPosition({0.f,5.f,0.f});

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
		light.LinkColor(defaultShader, "lightColor");
		light.LinkRotation(defaultShader, "lightDirection");

		viewport.linkCameraMatrix(lightShader, "cameraMatrix");
		light.LinkColor(lightShader, "lightColor");

		gridPlane.Draw(defaultShader);
		sphere.Draw(defaultShader);
		cubeStack.Draw(defaultShader);
		sword.Draw(defaultShader);

		light.DrawGizmo(lightShader);

		if (glfwGetKey(window.getWindowPtr(), GLFW_KEY_I) == GLFW_PRESS) {
			light.Rotate({0.0001f, 0.0f, 0.f});
		}
		if (glfwGetKey(window.getWindowPtr(), GLFW_KEY_K) == GLFW_PRESS) {
			light.Rotate({-0.0001f, 0.0f, 0.f});
		}
		if (glfwGetKey(window.getWindowPtr(), GLFW_KEY_J) == GLFW_PRESS) {
			light.Rotate({0.0f, -0.0001f, 0.f});
		}
		if (glfwGetKey(window.getWindowPtr(), GLFW_KEY_L) == GLFW_PRESS) {
			light.Rotate({0.0f, 0.0001f, 0.f});
		}
		if (glfwGetKey(window.getWindowPtr(), GLFW_KEY_APOSTROPHE) == GLFW_PRESS) {
			std::cout << "posx: " << viewport.position.x << std::endl;
			std::cout << "posy: " << viewport.position.y << std::endl;
			std::cout << "posz: " << viewport.position.z << std::endl;
			std::cout << "rotx: " << viewport.orientation.x << std::endl;
			std::cout << "roty: " << viewport.orientation.y << std::endl;
			std::cout << "rotz: " << viewport.orientation.z << std::endl;
		}

		window.measureTitleBarFPS(true);
		window.swapBuffers();
		window.measureTitleBarFPS(false);

	}

    defaultShader.Delete();
	lightShader.Delete();

    return 0;
}
