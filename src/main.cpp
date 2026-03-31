#ifdef __APPLE__
	#include <mach-o/dyld.h>  // macOS specific
#endif

#include "engine/input.h"
#include "engine/entities/model.h"
#include "engine/entities/light.h"

#include "imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "opengl/renderer/framebuffer.h"
#include "opengl/utils.h"

#include <chrono>
#include <thread>

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
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window.getWindowPtr(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	Viewport viewport(window.getWidth(), window.getHeight(), {-9.3,3.1,9.3}, {0,-45,0});
	
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

	Framebuffer postProcess(window.getWidth(), window.getHeight());
	Shader pp_edgeDetector("assets/shaders/pp_edgeDetector.vert", "assets/shaders/pp_edgeDetector.frag");
	pp_edgeDetector.Activate();
	glUniform1i(glGetUniformLocation(pp_edgeDetector.getID(), "screenTexture"), 0);

	Shader lightGizmo("assets/shaders/lightGizmo.vert", "assets/shaders/lightGizmo.frag");
	Framebuffer gizmoLayer(window.getWidth(), window.getHeight());
	Shader pp_default("assets/shaders/pp_default.vert", "assets/shaders/pp_default.frag");
	pp_default.Activate();
	glUniform1i(glGetUniformLocation(pp_default.getID(), "screenTexture"), 0);

	window.verticalSync(false);
	bool limitFPS = (true);	
	int fpsTarget = 60;
	float deltatime = 1.f;

	auto fpsSampleBegin = std::chrono::steady_clock::now();
	auto frametimeSum = std::chrono::nanoseconds(0);
	int sampleInterval = 1000;
	float avgFPS = 0;
	float sampledFrames = 0;

    // Main render loop
	while (!window.shouldClose())
	{
		auto frametimeTarget = std::chrono::duration<float, std::milli>(1000.0f / fpsTarget);
		auto frametimeStart = std::chrono::steady_clock::now();

		window.pollEvents();
		input.Update(viewport, deltatime, light);
		viewport.UpdateCameraMatrix(45.f, 0.1f, 100.0f);
		
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
		ImGui::Separator();
		ImGui::Text("FPS: %.2f",
			avgFPS
		);
		ImGui::InputInt("FPS Target", &fpsTarget);
		if (ImGui::Button("Vsync On")) {
			window.verticalSync(true);
		}
		
		ImGui::SameLine();
		ImGui::End();

		viewport.LinkCameraMatrix(pointLight, "cameraMatrix");
		viewport.LinkCameraPos(pointLight, "cameraPos");
		light.LinkColor(pointLight, "lightColor");
		light.LinkRotation(pointLight, "lightDirection");

		viewport.LinkCameraMatrix(lightGizmo, "cameraMatrix");
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
		light.Draw(lightGizmo);
		postProcess.FramebufferToWindow(pp_default);
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.swapBuffers();

		auto frametimeEnd = std::chrono::steady_clock::now();
		auto frametimeElapsed = frametimeEnd - frametimeStart;

		if (limitFPS && frametimeElapsed < frametimeTarget) {
			std::this_thread::sleep_for(frametimeTarget - (frametimeElapsed));
		}

		auto frametimeActual = std::chrono::steady_clock::now() - frametimeStart;
		deltatime = std::chrono::duration<float>(frametimeActual).count();

		frametimeSum += frametimeActual;
		sampledFrames += 1.f;
		if ((fpsSampleBegin + std::chrono::milliseconds(sampleInterval)) < std::chrono::steady_clock::now()) {
			avgFPS = 1000.f / (std::chrono::duration<float, std::milli>(frametimeSum).count() / sampledFrames); 
			fpsSampleBegin = std::chrono::steady_clock::now();
			frametimeSum = std::chrono::milliseconds(0);
			sampledFrames = 0;
		};
	}

 	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
    return 0;
}
