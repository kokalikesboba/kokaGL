#include "errorchecks.h"

#include "window/input.h"
#include "engine/runtime/framepacer.h"
#include "engine/scene/scene.h"

int main() {

    ErrorCheck::RequireMacDir();
    ErrorCheck::RequireAssetDir();

    Window window(800, 600, "kokaGL", GfxAPI::None);
	Input input(window);
    Framepacer framepacer;
	Scene scene("load/scene.json", true);
    scene.SetPrimaryCamera(0);

	while (!window.ShouldClose())
	{
		window.PollEvents();
        input.Update(scene.GetPrimaryCamera(), framepacer.GetDeltaTime());

		framepacer.Start();

        // Rendering goes here.

		framepacer.End();
	}
	
    return 0;
}
