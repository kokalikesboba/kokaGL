#ifdef __APPLE__
	#include <mach-o/dyld.h>  // macOS specific
#endif

#include "opengl/buffers/ubo.h"
#include "opengl/drawable/framebuffer.h"
//#include "opengl/renderer.h"

#include "engine/scene/assetmanager.h"
#include "engine/scene/model.h"
#include "engine/scene/gizmo.h"
#include "engine/scene/light.h"

#include "engine/runtime/framepacer.h"
#include "engine/runtime/rendermanager.h"

#include "window/input.h"
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
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindowPtr(), true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
	ImGui_ImplOpenGL3_Init();

	Framepacer framepacer;

	Shader mesh_phong("shaders/mesh_phong.vert", "shaders/mesh_phong.frag");
	Shader light_default("shaders/light_default.vert", "shaders/light_default.frag");
	Shader bb_default("shaders/bb_default.vert", "shaders/bb_default.frag");
	Shader pp_edge_detector("shaders/pp_edge_detector.vert", "shaders/pp_edge_detector.frag"); 	
	pp_edge_detector.UploadUni("screenTexture", 0);
	Shader pp_default("shaders/pp_default.vert", "shaders/pp_default.frag");
	pp_default.UploadUni("screenTexture", 0);
	Shader mesh_depth_map("shaders/mesh_depth_map.vert", "shaders/mesh_depth_map.frag");
	Shader pp_ssao("shaders/pp_ssao.vert", "shaders/pp_ssao.frag");

	Viewport viewport(window.GetFbWidth(), window.GetFbHeight());
	viewport.SetEulerRotation({0.f,315.f,0.f});
	viewport.SetPosition({-6.5f, 3.f, 6.5f});

	UBO vpubo(sizeof(viewportUBO), 0);
	vpubo.LinkBlock(mesh_phong, "viewportUBO");
	vpubo.LinkBlock(light_default, "viewportUBO");
	vpubo.LinkBlock(bb_default, "viewportUBO");
	vpubo.LinkBlock(mesh_depth_map,"viewportUBO");
	viewportUBO vpUpload;

    Light light({0.4f, 0.4f, 0.4f});

	AssetManager assets("scene.json");
    RenderManager renderer("resources.json", assets.getModelList(), assets.getGizmoList());

	// For the UI
	double cursorPosX, cursorPosY;
	bool desired_vsync = true;
	int desired_fps = 0;
	float nearPlane = 1.f;
	float farPlane = 40.f;
	float fov = 70.f;
	Shader* shaders[] = { &mesh_phong, &light_default, &bb_default,&pp_edge_detector, &pp_default, &mesh_depth_map, &pp_ssao };
	const char* shaderNames[] = { "mesh_phong", "light_default", "bb_default", "pp_edgeDetector", "pp_default", "mesh_depth_map", "pp_ssao" };
	int selectedShader = 0;
	
	while (!window.ShouldClose())
	{
		// gizmo.SetScale(2.f * glm::vec3(0.05f * cos(0.005f * framepacer.GetDeltaTime()) + 1.f));
		// glm::vec3 orbitCenter = {0.f, 1.f, 3.f};
		// float angle = 0.005f * framepacer.GetTime();
		// gizmo.SetPosition(orbitCenter + glm::vec3(sin(angle), 0.f, cos(angle)));

		window.PollEvents();
		viewport.Resize(window.GetFbWidth(), window.GetFbHeight());
		input.Update(viewport, framepacer.GetDeltaTime());
		framepacer.Start();

		vpUpload.matrix = viewport.GetViewportMatrix();
		vpUpload.orientation = glm::mat4_cast(viewport.GetOrientation());
		vpUpload.pos = viewport.GetPosition();
		vpubo.Update(vpUpload);
		
		mesh_phong.UploadUni("lightColor", light.getColor());
		mesh_phong.UploadUni("lightDirection", light.GetForwardAxis());
		light_default.UploadUni("lightColor", light.getColor());

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		assets.Draw(mesh_phong, bb_default);

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
			viewport.GetPosition().x, 
			viewport.GetPosition().y, 
			viewport.GetPosition().z
		);
		ImGui::Text("rX: %.2f  rY: %.2f  rZ: %.2f", 
			viewport.GetEulerRotation().x, 
			viewport.GetEulerRotation().y, 
			viewport.GetEulerRotation().z
		);
		ImGui::Text("Framebuffer: %i, / %i", (int)window.GetFbWidth(), (int)window.GetFbHeight());
		if (ImGui::DragFloat("Near", &nearPlane, 0.01f, 0.001f, 10.f))  viewport.SetNearPlane(nearPlane);
		if (ImGui::DragFloat("Far", &farPlane, 1.f, 1.f, 1000.f)) viewport.SetFarPlane(farPlane);
		if (ImGui::DragFloat("FOV", &fov, 0.5f, 10.f, 170.f))  viewport.SetFOV(fov);
		ImGui::Separator();

		if (ImGui::Button("Reload Model Manifest")) {
			assets.Reload();
		}
		if (ImGui::Button("Save Model Manifet")) {
			assets.SaveCurrentArrangement();
		}
		ImGui::ListBox("Shaders", &selectedShader, shaderNames, IM_ARRAYSIZE(shaderNames));
		if (ImGui::Button("Reload Selected Shader")) {
			shaders[selectedShader]->Reload();
		}
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
