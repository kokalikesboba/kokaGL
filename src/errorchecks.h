#include <filesystem>

#ifdef __APPLE__
	#include <mach-o/dyld.h>  // macOS specific
#endif

namespace ErrorCheck {

inline void RequireMacDir() {
    #ifdef __APPLE__
        uint32_t size = PATH_MAX;
        char exePath[PATH_MAX];
        _NSGetExecutablePath(exePath, &size);

        std::filesystem::path dir = std::filesystem::path(exePath).parent_path();
        std::filesystem::current_path(dir);
    #endif
}

inline void RequireSceneManifest() {
    if (!std::filesystem::exists("data/scene.json")) {
        throw std::runtime_error("Missing data/scene.json");
    }
}

inline void RequireRenderManifest() {
    if (!std::filesystem::exists("data/renderer.json")) {
        throw std::runtime_error("Missing data/renderer.json");
    }
}

}