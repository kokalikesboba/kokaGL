#include "errorchecks.h"

#include "window/window.h"
#include "window/input.h"

#include "engine/runtime/framepacer.h"
#include "engine/scene/scene.h"
#include "opengl/renderer.h"

#include "window/ui.h"

int main() {

    ErrorCheck::RequireMacDir();
    ErrorCheck::RequireAssetDir();

    Window window(800, 600, "kokaGL", GfxAPI::OpenGL);
    window.MakeContextCurrent();
	Input input(window);
    Framepacer framepacer;
	Scene scene("data/scene.json", true);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) throw std::runtime_error("Failed to init GLAD");
    
    DearUI ui(window);
    Renderer renderer("data/renderer.json", scene);
	
	while (!window.ShouldClose())
	{
		window.PollEvents();
		input.Update(scene.GetPrimaryCamera(), framepacer.GetDeltaTime());
		framepacer.Start();

        renderer.Clear({0.07f, 0.13f, 0.17f, 1.0f});
        renderer.UpdateUniforms(window.GetFbWidth(), window.GetFbHeight());
        renderer.DrawModels();
        renderer.DrawGizmo();

        ui.NewFrame();


        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Purge Models")) {
                    scene.PurgeModels();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Window")) {
                ui.SubmitWindowDimensionStats();
                ui.SubmitWindowFullscreenToggle();
                ui.SubmitWindowVsyncToggle();
                ImGui::Separator();
                ui.SubmitFramepacerStats(framepacer);
                ui.SubmitFramepacerEnterTargetFPS(framepacer);
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Models")) {
                for (const auto& model : scene.GetModelList()) {
                    if (ImGui::BeginMenu(model->name.c_str())) {
                        if (ImGui::Checkbox("Draw", &model->wantsToBeDrawn));
                        ImGui::EndMenu();
                    }
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Cameras")) {
                int cameraCount = 0;
                for (const auto& cameras : scene.GetCameraList()) {
                    ++cameraCount;
                    if (ImGui::BeginMenu(std::string("Camera " + std::to_string(cameraCount)).c_str())) {
                        ui.SubmitCameraStats(scene.GetPrimaryCamera());
                        ImGui::Separator();
                        ui.SubmitCameraEnterPlanes(*cameras);

                        ImGui::EndMenu();
                    }   
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Lights")) {
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();  // inside
        }

        ui.Draw();

		window.SwapBuffers();

		framepacer.End();
	}
    return 0;
}
