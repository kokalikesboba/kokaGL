#!/bin/bash
IMGUI=extern/imgui

# Keep only what you use
keep=(
    imgui.h
    imgui.cpp
    imgui_internal.h
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
    imconfig.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    backends/imgui_impl_glfw.h
    backends/imgui_impl_glfw.cpp
    backends/imgui_impl_opengl3.h
    backends/imgui_impl_opengl3.cpp
    backends/imgui_impl_opengl3_loader.h
)

# Move kept files out temporarily
mkdir -p /tmp/imgui_keep/backends
for f in "${keep[@]}"; do
    cp "$IMGUI/$f" "/tmp/imgui_keep/$f"
done

# Nuke and rebuild
rm -rf "$IMGUI"
mkdir -p "$IMGUI/backends"
for f in "${keep[@]}"; do
    cp "/tmp/imgui_keep/$f" "$IMGUI/$f"
done

rm -rf /tmp/imgui_keep
echo "Done"
