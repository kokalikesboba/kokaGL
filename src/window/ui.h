#ifndef UI_H
#define UI_H

#include "imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "window/window.h"
#include "engine/scene/scene.h"
#include "engine/runtime/framepacer.h"
#include "opengl/renderer.h"

class DearUI {
public:
    DearUI(Window &window);
    void NewFrame();
    void Draw();

    // Immutable window entries
    void SubmitWindowDimensionStats() const;
    // Mutable window entries
    void SubmitWindowVsyncToggle();
    void SubmitWindowFullscreenToggle();
    
    // Immutable framepacer entries
    void SubmitFramepacerStats(const Framepacer& framepacer) const;
    // Mutable framepacer entries
    void SubmitFramepacerEnterTargetFPS(Framepacer& framepacer);

    // Immutable camera entries
    void SubmitCameraStats(const Camera& camera) const;
    // Mutable camera entries
    void SubmitCameraEnterPlanes(Camera& camera);

    // Mutable scene entries
    void SubmitSceneReload(Scene& scene, Renderer& renderer); 

    ~DearUI();

private:

    Window &window;
    int fontSize = 9;

    // Window
	bool desired_vsync = true;

    // Framepacer
	int desired_fps = 0;

    // Camera
	float nearPlane = 1.f;
	float farPlane = 40.f;
	float fov = 70.f;

};

#endif