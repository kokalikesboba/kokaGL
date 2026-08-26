#include "errorchecks.h"

#include "window/window.h"
#include "window/input.h"

#include "engine/runtime/framepacer.h"
#include "engine/scene/scene.h"

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
    
    DearUI ui(window);
	
	while (!window.ShouldClose())
	{
		window.PollEvents();
		input.Update(scene.GetPrimaryCamera(), framepacer.GetDeltaTime());
		framepacer.Start();

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
