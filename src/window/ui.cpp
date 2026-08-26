#include "ui.h"

DearUI::DearUI(Window &window) 
: 
window(window)
{
    IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = ".imgui.ini";

    fontSize = int(fontSize) * (float(window.GetFbHeight()) / float(window.GetHeight()));

	ImFont* font1 = io.Fonts->AddFontFromFileTTF("assets/fonts/Fredoka.ttf", fontSize);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui_ImplGlfw_InitForOpenGL(window.Get(), true);
	ImGui_ImplOpenGL3_Init();
}

void DearUI::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame(); 
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Debug", nullptr);
}

void DearUI::Draw()
{
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DearUI::SubmitWindowDimensionStats() const
{
    double cursorPosX, cursorPosY;
    ImGui::Text("Window: %i, /  %i", (int)window.GetWidth(),(int)window.GetHeight());
    glfwGetCursorPos(window.Get(), &cursorPosX, &cursorPosY);
    ImGui::Text("Cursor Position X: %.i  Y: %.i", (int)cursorPosX, (int)cursorPosY);
    ImGui::Text("Framebuffer: %i, / %i", (int)window.GetFbWidth(), (int)window.GetFbHeight());
}

void DearUI::SubmitWindowVsyncToggle()
{
    ImGui::Checkbox("Wait for Vsync", &desired_vsync);
    if (desired_vsync) window.VerticalSync(true);
    else window.VerticalSync(false);
}

void DearUI::SubmitWindowFullscreenToggle()
{
    if (ImGui::Button("Enable Fullscreen")) {
        window.EnableFullscreen();
    };
    ImGui::SameLine();
    if (ImGui::Button("Disable Fullscreen")) {
        window.DisableFullscreen();
    };
}

void DearUI::SubmitFramepacerStats(const Framepacer &framepacer) const
{
    ImGui::Text("FPS: %.2f",
        framepacer.GetAvgFPS()
    );
}

void DearUI::SubmitFramepacerEnterTargetFPS(Framepacer& framepacer)
{
    ImGui::InputInt("Input FPS", &desired_fps);
    if (ImGui::Button("Apply FPS")) {
        framepacer.SetTargetFramerate(desired_fps);
    };
}

void DearUI::SubmitCameraStats(const Camera& camera) const
{
    ImGui::Text("X: %.2f  Y: %.2f  Z: %.2f", 
    camera.GetPosition().x, 
    camera.GetPosition().y, 
    camera.GetPosition().z
    );
    ImGui::Text("rX: %.2f  rY: %.2f  rZ: %.2f", 
        camera.GetEulerRotation().x, 
        camera.GetEulerRotation().y, 
        camera.GetEulerRotation().z
    );
}

void DearUI::SubmitCameraEnterPlanes(Camera& camera)
{
    if (ImGui::DragFloat("Near", &nearPlane, 0.01f, 0.001f, 10.f)) camera.SetNearPlane(nearPlane);
    if (ImGui::DragFloat("Far", &farPlane, 1.f, 1.f, 1000.f)) camera.SetFarPlane(farPlane);
    if (ImGui::DragFloat("FOV", &fov, 0.5f, 10.f, 170.f))  camera.SetFOV(fov);
}

void DearUI::SubmitSceneReload(Scene& scene, Renderer& renderer)
{
    if (ImGui::Button("Reload Model Manifest")) {
        scene.Reload();
        renderer.RebuildScene();
    }
}

DearUI::~DearUI()
{
    ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}