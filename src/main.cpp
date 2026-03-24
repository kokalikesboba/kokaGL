#include "engine/input.h"
#include "engine/entities/model.h"
#include "engine/entities/light.h"

#include "imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "opengl/renderer/framebuffer.h"

int main() {

    GlfwContext glfw;
    Window window(1000, 1000, "kokaGL");
    window.makeContextCurrent();

	Input input(window.getWindowPtr());
	
    // Load OpenGL function pointers via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font1 = io.Fonts->AddFontFromFileTTF("assets/fonts/Fredoka.ttf", 13.f);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window.getWindowPtr(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	Viewport viewport(window.getWidth(), window.getHeight(), {0,3,10}, {0,0,-1});
	
	// Create and link the shader program from source file6s
    Shader pointLight("assets/shaders/pointLight.vert", "assets/shaders/pointLight.frag");

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
	light.SetOrientation({glm::radians(155.f), glm::radians(45.f),0});

	Framebuffer postProcess(window.getWidth(), window.getHeight());
	Shader pp_edgeDetector("assets/shaders/pp_edgeDetector.vert", "assets/shaders/pp_edgeDetector.frag");
	pp_edgeDetector.Activate();
	glUniform1i(glGetUniformLocation(pp_edgeDetector.getID(), "screenTexture"), 0);

	Shader lightGizmo("assets/shaders/lightGizmo.vert", "assets/shaders/lightGizmo.frag");
	Framebuffer gizmoLayer(window.getWidth(), window.getHeight());
	Shader pp_default("assets/shaders/pp_default.vert", "assets/shaders/pp_default.frag");
	pp_default.Activate();
	glUniform1i(glGetUniformLocation(pp_default.getID(), "screenTexture"), 0);

    // Main render loop
	while (!window.shouldClose())
	{
		window.pollEvents();
		input.Update(viewport, light);
		viewport.updateCameraMatrix(45.f, 0.1f, 100.0f);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Camera");
		ImGui::Text("Position");
		ImGui::Text("X: %.2f  Y: %.2f  Z: %.2f", 
			viewport.position.x, 
			viewport.position.y, 
			viewport.position.z
		);
		ImGui::Separator();
		ImGui::Text("Orientation");
		ImGui::Text("X: %.2f  Y: %.2f  Z: %.2f",
			viewport.orientation.x,
			viewport.orientation.y,
			viewport.orientation.z
		);

		double cursorPosX, cursorPosY;
		glfwGetCursorPos(window.getWindowPtr(), &cursorPosX, &cursorPosY);
		ImGui::Separator();
		ImGui::Text("Cursor Position");
		ImGui::Text("X: %.2f  Y: %.2f", (float)cursorPosX, (float)cursorPosY);
		ImGui::End();

		viewport.linkCameraMatrix(pointLight, "cameraMatrix");
		viewport.linkCameraPos(pointLight, "cameraPos");
		light.LinkColor(pointLight, "lightColor");
		light.LinkRotation(pointLight, "lightDirection");

		viewport.linkCameraMatrix(lightGizmo, "cameraMatrix");
		light.LinkColor(lightGizmo, "lightColor");

		postProcess.RenderToFramebuffer();
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		gridPlane.Draw(pointLight);
		sphere.Draw(pointLight);
		cubeStack.Draw(pointLight);
		sword.Draw(pointLight);
		postProcess.FramebufferToWindow(pp_default);

		gizmoLayer.RenderToFramebuffer();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		light.DrawGizmo(lightGizmo);
		gizmoLayer.FramebufferToWindow(pp_default);

		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.measureTitleBarFPS(true);
		window.swapBuffers();
		window.measureTitleBarFPS(false);
	}

 	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
    return 0;
}
