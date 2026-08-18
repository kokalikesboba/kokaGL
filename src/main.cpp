#ifdef __APPLE__
	#include <mach-o/dyld.h>  // macOS specific
#endif

#include "window/window.h"
#include "window/input.h"

#include "engine/runtime/framepacer.h"
#include "engine/scene/scene.h"
#include "engine/runtime/renderer.h"

#include "window/ui.h"

int main() {

	#ifdef __APPLE__
        #include <filesystem>
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

    // Variables here are independent from the rendering backend! Yay!
    GlfwContext glfw;
    Window window(800, 600, "kokaGL", false);
    window.MakeContextCurrent();
	Input input(window);
    Framepacer framepacer;
	Scene scene("scene.json", true);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to init GLAD\n";
        return -1;
    }

    DearUI ui(window);
    Renderer renderer("renderer.json", scene);

    auto& camera = scene.GetCameraList();
	
	while (!window.ShouldClose())
	{
		window.PollEvents();
		input.Update(*camera[0], framepacer.GetDeltaTime());
		framepacer.Start();

        renderer.Clear({0.07f, 0.13f, 0.17f, 1.0f});
        renderer.UpdateUniforms(window.GetFbWidth(), window.GetFbHeight());
        renderer.DrawModels();
        renderer.DrawGizmo();

        ui.NewFrame();
        ui.Draw();
        
		window.SwapBuffers();

		framepacer.End();
	}
    return 0;
}
