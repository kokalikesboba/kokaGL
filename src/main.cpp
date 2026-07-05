#ifdef __APPLE__
	#include <mach-o/dyld.h>  // macOS specific
#endif

#include "opengl/buffers/ubo.h"
#include "opengl/drawable/framebuffer.h"
#include "opengl/utils.h"

#include "engine/runtime/texturepool.h"
#include "engine/scene/model.h"
#include "engine/scene/gizmo.h"
#include "engine/scene/light.h"

#include "engine/runtime/framepacer.h"
#include "engine/runtime/input.h"

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

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    GlfwContext glfw;

    Window window(800, 800, "kokaGL");
    window.makeContextCurrent();

	Input input(window.getWindowPtr());

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

	Framepacer framepacer;

	Shader mesh_phong("shaders/mesh_phong.vert", "shaders/mesh_phong.frag");
	Shader light_default("shaders/light_default.vert", "shaders/light_default.frag");
	Shader bb_default("shaders/bb_default.vert", "shaders/bb_default.frag");
	Shader pp_edge_detector("shaders/pp_edge_detector.vert", "shaders/pp_edge_detector.frag");
	pp_edge_detector.UploadUni("screenTexture", 0);
	Shader pp_default("shaders/pp_default.vert", "shaders/pp_default.frag");
	pp_default.UploadUni("screenTexture", 0);
	Shader mesh_depth_map("shaders/mesh_depth_map.vert", "shaders/mesh_depth_map.frag");

	Viewport viewport(window.getFbWidth(), window.getFbHeight());
	viewport.SetEulerRotation({0.f,315.f,0.f});
	viewport.SetPosition({-6.5f, 3.f, 6.5f});

	UBO vpubo(sizeof(viewportUBO), 0);
	vpubo.LinkBlock(mesh_phong, "viewportUBO");
	vpubo.LinkBlock(light_default, "viewportUBO");
	vpubo.LinkBlock(bb_default, "viewportUBO");
	vpubo.LinkBlock(mesh_depth_map,"viewportUBO");
	viewportUBO vpUpload;

	TexturePool texturepool;

	Gizmo gizmo("assets/images/sammy_pixelvap.png");
	gizmo.AddPosition({0.f, 5.f, 0.f});

	Light light({1.f,1.f,1.f});
	light.SetPosition({0.f,5.f,0.f});

	// Ground plane — origin, the floor everything sits on.
	Model gridPlane("assets/models/plane.glb", texturepool);
	gridPlane.SetPosition({0.0f, 0.0f, 0.0f});

	// Sphere — front-right, raised so it reads as floating / hero object.
	Model sphere("assets/models/sphere.glb", texturepool);
	sphere.SetPosition({3.5f, 1.5f, 2.0f});

	// Sword — center stage, tilted as if planted point-down in the ground.
	Model sword("assets/models/sword.glb", texturepool);
	sword.SetPosition({0.0f, 1.0f, 0.0f});
	sword.SetEulerRotation({0.0f, 45.0f, 180.0f});

	// Chest — front-left, the new model, angled toward the camera.
	Model chest("assets/models/chest.glb", texturepool);
	chest.SetPosition({-3.0f, 0.1f, 2.5f});
	chest.SetEulerRotation({0.0f, -30.0f, 0.0f});

	// Monkey — back-right, scaled up a touch as a focal character.
	Model monkey("assets/models/icoStack.glb", texturepool);
	monkey.SetPosition({3.0f, 0.1f, -3.0f});
	monkey.SetEulerRotation({0.0f, 200.0f, 0.0f});

	// Pointer — small, near origin, your gizmo/indicator model.
	Model pointer("assets/models/pointer.glb", texturepool);
	pointer.SetPosition({1.5f, 0.1f, 1.5f});

	// error.glb — off to the side as the deliberate "this one's the test" model.
	Model error("assets/models/error.glb", texturepool);
	error.SetPosition({0.0f, 0.1f, -5.0f});

	Framebuffer framebuffer0(window.getFbWidth(), window.getFbHeight());
	Framebuffer framebuffer1(window.getFbWidth(), window.getFbHeight());
	
	// For the UI
	bool desired_vsync = true;
	int desired_fps = 0;
	Shader* shaders[] = { &mesh_phong, &light_default, &bb_default,&pp_edge_detector, &pp_default };
	const char* shaderNames[] = { "mesh_phong", "light_default", "bb_default", "pp_edgeDetector", "pp_default" };
	int selectedShader = 0;
	
	while (!window.shouldClose())
	{
		light.AddEulerRotation({16.f * framepacer.deltatime,0.f,0.f});
		sphere.AddEulerRotation({50.f * framepacer.deltatime,0.f,0.f});
		gizmo.SetScale(2.f * glm::vec3(0.05f * cos(0.005f * framepacer.Time()) + 1.f));
		glm::vec3 orbitCenter = {0.f, 1.f, 3.f};
		float angle = 0.005f * framepacer.Time();
		gizmo.SetPosition(orbitCenter + glm::vec3(sin(angle), 0.f, cos(angle)));

		window.pollEvents();
		// TODO: Leaky
		input.Update(viewport, framepacer.deltatime, light);
		framepacer.Start();

		vpUpload.matrix = viewport.GetViewportMatrix();
		vpUpload.orientation = glm::mat4_cast(viewport.GetOrientation());
		vpUpload.pos = viewport.GetPosition();
		vpubo.Update(vpUpload);
		
		mesh_phong.UploadUni("lightColor", light.getColor());
		mesh_phong.UploadUni("lightDirection", light.GetForwardAxis());
		light_default.UploadUni("lightColor", light.getColor());

		framebuffer0.DrawToFramebuffer();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gridPlane.Draw(mesh_phong);
		sphere.Draw(mesh_phong);
		sword.Draw(mesh_phong);
		chest.Draw(mesh_phong);
		gizmo.Draw(bb_default);

		glDisable(GL_CULL_FACE);

		framebuffer0.DrawToWindow(pp_default);

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
			glm::eulerAngles(viewport.GetOrientation()).x,
			glm::eulerAngles(viewport.GetOrientation()).y,
			glm::eulerAngles(viewport.GetOrientation()).z
		);
		ImGui::Separator();

		ImGui::ListBox("Shaders", &selectedShader, shaderNames, IM_ARRAYSIZE(shaderNames));
		if (ImGui::Button("Reload Selected")) {
			shaders[selectedShader]->Reload();
		}
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
