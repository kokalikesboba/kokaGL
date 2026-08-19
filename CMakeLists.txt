cmake_minimum_required(VERSION 4.0.0)
project(kokaGL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(imgui STATIC
    extern/imgui/imgui.cpp
    extern/imgui/imgui_draw.cpp
    extern/imgui/imgui_tables.cpp
    extern/imgui/imgui_widgets.cpp
    extern/imgui/imgui_demo.cpp
    extern/imgui/backends/imgui_impl_glfw.cpp
    extern/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC extern/imgui extern/imgui/backends)
target_link_libraries(imgui PRIVATE glfw)

add_library(glad STATIC
    extern/glad/glad.c
)
target_include_directories(glad PUBLIC extern)

add_library(simdjson STATIC
    extern/simdjson/simdjson.cpp
)
target_include_directories(simdjson PUBLIC extern/simdjson)

add_library(fastgltf STATIC
    extern/fastgltf/src/fastgltf.cpp
    extern/fastgltf/src/base64.cpp
	extern/fastgltf/src/io.cpp
)
target_include_directories(fastgltf PUBLIC extern)
target_link_libraries(fastgltf PRIVATE simdjson)

add_library(stb_img STATIC
    extern/stb/stb.cpp
)
target_include_directories(stb_img PUBLIC extern)

add_executable(kokaGL)
target_sources(kokaGL PRIVATE
    src/main.cpp
    src/window/window.cpp
    src/window/input.cpp
    src/window/ui.cpp
    src/math/transform.cpp
    src/opengl/instance.cpp
    src/opengl/buffers/vao.cpp
    src/opengl/buffers/vbo.cpp
    src/opengl/buffers/ebo.cpp
    src/opengl/buffers/ubo.cpp
    src/opengl/buffers/fbo.cpp
    src/opengl/resources/texture.cpp
    src/opengl/resources/shader.cpp
    src/opengl/resources/viewport.cpp
    src/opengl/drawable/mesh.cpp
    src/opengl/drawable/billboard.cpp
    src/opengl/drawable/framebuffer.cpp
    src/opengl/texturemap.cpp
    src/opengl/instance.cpp
    src/opengl/renderer.cpp
    src/engine/parsers/gltf.cpp
    src/engine/parsers/png.cpp
    src/engine/runtime/framepacer.cpp
    src/engine/scene/model.cpp
    src/engine/scene/gizmo.cpp
    src/engine/scene/lamp.cpp
    src/engine/scene/scene.cpp
    src/engine/scene/camera.cpp
)
target_compile_features(kokaGL PRIVATE cxx_std_23)
target_include_directories(kokaGL PRIVATE
    src
)
target_link_libraries(kokaGL PRIVATE
    glfw
    OpenGL::GL
    imgui
    glad
    fastgltf
    stb_img
)
set_target_properties(kokaGL PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)