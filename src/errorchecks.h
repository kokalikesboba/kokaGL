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

inline void RequireAssetDir() {
    if (std::filesystem::is_empty("assets")) {
        throw std::runtime_error(
            "Error: assets directory is empty. \n Did you forget --recurse-submodules? \n Try: git submodule update --init\n"
        );
    }
}
}