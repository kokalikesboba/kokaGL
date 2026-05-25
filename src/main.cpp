#ifdef __APPLE__
	#include <mach-o/dyld.h>  // macOS specific
#endif

#include "engine/runtime/framepacer.h"
#include "engine/runtime/input.h"

#include "engine/entities/model.h"
#include "engine/entities/light.h"

#include "imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "opengl/drawable/framebuffer.h"
#include "opengl/utils.h"


int main() {

	#ifdef __APPLE__
		uint32_t size = PATH_MAX;
		char exePath[PATH_MAX];
		_NSGetExecutablePath(exePath, &size);

		std::filesystem::path dir = std::filesystem::path(exePath).parent_path();
		std::filesystem::current_path(dir);
	#endif
	
    GlfwContext glfw;

    Window window(800, 800, "kokaGL");
    window.makeContextCurrent();

	Framepacer framepacer;

	Input input(window.getWindowPtr());

    // Load OpenGL function pointers via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

	// printGPUSpecs();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font1 = io.Fonts->AddFontFromFileTTF("assets/fonts/Fredoka.ttf", 13.f);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window.getWindowPtr(), true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	Viewport viewport(window.getFbWidth(), window.getFbHeight());

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

	Framebuffer postProcess(window.getFbWidth(), window.getFbHeight());
	Shader pp_edgeDetector("assets/shaders/pp_edgeDetector.vert", "assets/shaders/pp_edgeDetector.frag");
	pp_edgeDetector.Activate();
	glUniform1i(glGetUniformLocation(pp_edgeDetector.getID(), "screenTexture"), 0);

	Shader lightGizmo("assets/shaders/lightGizmo.vert", "assets/shaders/lightGizmo.frag");
	Framebuffer gizmoLayer(window.getFbWidth(), window.getFbHeight());
	Shader pp_default("assets/shaders/pp_default.vert", "assets/shaders/pp_default.frag");
	pp_default.Activate();
	glUniform1i(glGetUniformLocation(pp_default.getID(), "screenTexture"), 0);

	// For the UI
	bool desired_vsync = true;
	int desired_fps = 0;
	
	while (!window.shouldClose())
	{
		framepacer.Start();
		
		window.pollEvents();
		input.Update(viewport, framepacer.deltatime, light);
		
		viewport.LinkViewportMatrix(pointLight, "cameraMatrix");
		viewport.LinkViewportPos(pointLight, "cameraPos");
		light.LinkColor(pointLight, "lightColor");
		light.LinkRotation(pointLight, "lightDirection");

		viewport.LinkViewportMatrix(lightGizmo, "cameraMatrix");
		light.LinkColor(lightGizmo, "lightColor");

		postProcess.RenderToFramebuffer();	
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		gridPlane.Draw(pointLight);
		sphere.Draw(pointLight);
		cubeStack.Draw(pointLight);
		sword.Draw(pointLight);
		light.Draw(lightGizmo);
		postProcess.FramebufferToWindow(pp_default);
		
		ImGui_ImplOpenGL3_NewFrame(); 
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoMove);

		ImGui::Text("Window width / height");
		ImGui::Text("Logical: %i, /  %i", (int)window.getWidth(),(int)window.getHeight());
		ImGui::Text("Framebuffer: %i, / %i", (int)window.getFbWidth(), (int)window.getFbHeight());
		ImGui::Separator();

		ImGui::Text("FPS: %.2f",
			framepacer.avgFPS
		);
		ImGui::InputInt("Input FPS", &desired_fps);
		if (ImGui::Button("Apply FPS")) {
			    framepacer.targetFramerate(desired_fps);
		};
		ImGui::SameLine();
		ImGui::Checkbox("Wait for Vsync", &desired_vsync);
		if (desired_vsync) window.verticalSync(true);
		else window.verticalSync(false);
		ImGui::Separator();

		double cursorPosX, cursorPosY;
		glfwGetCursorPos(window.getWindowPtr(), &cursorPosX, &cursorPosY);
		ImGui::Text("Cursor Position");
		ImGui::Text("X: %.2f  Y: %.2f", (float)cursorPosX, (float)cursorPosY);
		ImGui::Separator();

		ImGui::Text("Viewport Position");
		ImGui::Text("X: %.2f  Y: %.2f  Z: %.2f", 
			viewport.GetPosition().x, 
			viewport.GetPosition().y, 
			viewport.GetPosition().z
		);
		ImGui::Separator();
		
		ImGui::Text("Viewport Rotation");
		ImGui::Text("X: %.2f  Y: %.2f  Z: %.2f",
			glm::eulerAngles(viewport.GetRotation()).x,
			glm::eulerAngles(viewport.GetRotation()).y,
			glm::eulerAngles(viewport.GetRotation()).z
		);
		ImGui::Separator();

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		window.swapBuffers();

		framepacer.End();
	}

 	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
    return 0;
}
