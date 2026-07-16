#ifdef __APPLE__
	#include <mach-o/dyld.h>  // macOS specific
#endif

#include "window/input.h"

#include "engine/scene/scene.h"
#include "engine/runtime/renderer.h"
#include "engine/runtime/framepacer.h"

#include "imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <filesystem>

int main() {

	#ifdef __APPLE__
		uint32_t size = PATH_MAX;
		char exePath[PATH_MAX];
		_NSGetExecutablePath(exePath, &size);

		std::filesystem::path dir = std::filesystem::path(exePath).parent_path();
		std::filesystem::current_path(dir);
	#endif
	
	if (std::filesystem::is_empty("assets")) {
		std::cerr << "Error: assets directory is empty.\n"
				<< "Did you forget --recurse-submodules?\n"
				<< "Try: git submodule update --init\n";
		return -1;
	}

    GlfwContext glfw;
    Window window(800, 600, "kokaGL", true);
    window.MakeContextCurrent();
	Input input(window.GetWindowPtr());

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font1 = io.Fonts->AddFontFromFileTTF("assets/fonts/Fredoka.ttf", 13.f);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindowPtr(), true);
	ImGui_ImplOpenGL3_Init();

    Framepacer framepacer;
	Scene scene("scene.json");  
    Light light({0.4f, 0.4f, 0.4f});
    Renderer renderer("renderer.json", scene);

	// For the UI
    auto& cameras = scene.GetCameraList();

	double cursorPosX, cursorPosY;
	bool desired_vsync = true;
	int desired_fps = 0;
	float nearPlane = 1.f;
	float farPlane = 40.f;
	float fov = 70.f;
	Shader* shaders[] = {  };
	const char* shaderNames[] = { "mesh_phong", "light_default", "bb_default", "pp_edgeDetector", "pp_default", "mesh_depth_map", "pp_ssao" };
	int selectedShader = 0;
	
	while (!window.ShouldClose())
	{
		// gizmo.SetScale(2.f * glm::vec3(0.05f * cos(0.005f * framepacer.GetDeltaTime()) + 1.f));
		// glm::vec3 orbitCenter = {0.f, 1.f, 3.f};
		// float angle = 0.005f * framepacer.GetTime();
		// gizmo.SetPosition(orbitCenter + glm::vec3(sin(angle), 0.f, cos(angle)));

		window.PollEvents();
		input.Update(*cameras[0], framepacer.GetDeltaTime());
		framepacer.Start();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.Draw(window.GetFbWidth(), window.GetFbHeight());

		ImGui_ImplOpenGL3_NewFrame(); 
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoMove);

		ImGui::Text("Window: %i, /  %i", (int)window.GetWidth(),(int)window.GetHeight());
		glfwGetCursorPos(window.GetWindowPtr(), &cursorPosX, &cursorPosY);
		ImGui::Text("Cursor Position X: %.i  Y: %.i", (int)cursorPosX, (int)cursorPosY);
		ImGui::Separator();

		ImGui::Text("FPS: %.2f",
			framepacer.GetAvgFPS()
		);
		ImGui::InputInt("Input FPS", &desired_fps);
		if (ImGui::Button("Apply FPS")) {
			framepacer.SetTargetFramerate(desired_fps);
		};
		ImGui::SameLine();
		ImGui::Checkbox("Wait for Vsync", &desired_vsync);
		if (desired_vsync) window.VerticalSync(true);
		else window.VerticalSync(false);
		ImGui::Separator();

		ImGui::Text("X: %.2f  Y: %.2f  Z: %.2f",
			cameras[0]->GetPosition().x,
			cameras[0]->GetPosition().y,
			cameras[0]->GetPosition().z
		);
		ImGui::Text("rX: %.2f  rY: %.2f  rZ: %.2f",
			cameras[0]->GetEulerRotation().x,
			cameras[0]->GetEulerRotation().y,
			cameras[0]->GetEulerRotation().z
		);
		ImGui::Text("Framebuffer: %i, / %i", (int)window.GetFbWidth(), (int)window.GetFbHeight());
		if (ImGui::DragFloat("Near", &nearPlane, 0.01f, 0.001f, 10.f)) cameras[0]->SetNearPlane(nearPlane);
		if (ImGui::DragFloat("Far", &farPlane, 1.f, 1.f, 1000.f)) cameras[0]->SetFarPlane(farPlane);
		if (ImGui::DragFloat("FOV", &fov, 0.5f, 10.f, 170.f))  cameras[0]->SetFOV(fov);
		ImGui::Separator();


		if (ImGui::Button("Reload Model Manifest")) {
			scene.Reload();
		}
        /*
		if (ImGui::Button("Save Model Manifet")) {
			scene.SaveCurrentArrangement();
		}
		ImGui::ListBox("Shaders", &selectedShader, shaderNames, IM_ARRAYSIZE(shaderNames));
		if (ImGui::Button("Reload Selected Shader")) {
			shaders[selectedShader]->Reload();
		}
        */
		ImGui::Separator();

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
		window.SwapBuffers();

		framepacer.End();
	}

 	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
    return 0;
}
