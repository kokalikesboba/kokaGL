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

	while (!window.ShouldClose())
	{
		window.PollEvents();

		framepacer.Start();

        // Rendering happens here.

		framepacer.End();
	}
	
    return 0;
}
