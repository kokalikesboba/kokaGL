#include "errorchecks.h"

#include "window/window.h"
#include "window/input.h"

#include "engine/runtime/framepacer.h"
#include "engine/scene/scene.h"
#include "engine/runtime/renderer.h"

#include "window/ui.h"

int main() {

    ErrorCheck::RequireMacDir();
    ErrorCheck::RequireAssetDir();

    Window window(800, 600, "kokaGL", GfxAPI::OpenGL);
    window.MakeContextCurrent();
	Input input(window);
    Framepacer framepacer;
	Scene scene("data/scene.json", true);
    scene.SetPrimaryCamera(0);

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
        ui.SubmitWindowDimensionStats();
        ui.SubmitWindowFullscreenToggle();
        ui.SubmitWindowVsyncToggle();
        ui.SubmitFramepacerStats(framepacer);
        ui.SubmitFramepacerEnterTargetFPS(framepacer);
        ui.SubmitCameraStats(scene.GetPrimaryCamera());
        ui.SubmitCameraEnterPlanes(scene.GetPrimaryCamera());
        ui.Draw();
        
		window.SwapBuffers();

		framepacer.End();
	}
    return 0;
}
