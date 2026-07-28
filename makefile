EXTERN = extern

CXX = clang++
CC  = clang

CXXFLAGS = -g -O2 -std=c++23 -I$(EXTERN) -I$(EXTERN)/KHR -I$(EXTERN)/imgui -Isrc -I$(EXTERN)/simdjson
CFLAGS   = -g -O2 -I$(EXTERN) -I$(EXTERN)/KHR -I$(EXTERN)/imgui -Isrc

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    CXXFLAGS += -I/opt/homebrew/include
    CFLAGS   += -I/opt/homebrew/include
    LDLIBS    = -lglfw -framework OpenGL
    LDFLAGS  += -L/opt/homebrew/lib
else
    LDLIBS    = -lglfw -lGL -ldl
endif

MAKEFLAGS += -j10

TARGET = kokaGL

CPP_SRCS = \
	$(EXTERN)/stb/stb.cpp \
	$(EXTERN)/simdjson/simdjson.cpp \
	$(EXTERN)/fastgltf/src/fastgltf.cpp \
    $(EXTERN)/fastgltf/src/base64.cpp \
	$(EXTERN)/fastgltf/src/io.cpp \
	$(EXTERN)/imgui/imgui.cpp \
	$(EXTERN)/imgui/imgui_draw.cpp \
	$(EXTERN)/imgui/imgui_tables.cpp \
	$(EXTERN)/imgui/imgui_widgets.cpp \
	$(EXTERN)/imgui/imgui_demo.cpp \
	$(EXTERN)/imgui/backends/imgui_impl_glfw.cpp \
	$(EXTERN)/imgui/backends/imgui_impl_opengl3.cpp \
	src/window/window.cpp \
	src/math/transform.cpp \
	src/opengl/buffers/vao.cpp \
	src/opengl/buffers/vbo.cpp \
	src/opengl/buffers/ebo.cpp \
	src/opengl/buffers/ubo.cpp \
	src/opengl/buffers/fbo.cpp \
	src/opengl/resources/texture.cpp \
	src/opengl/resources/shader.cpp \
	src/opengl/resources/viewport.cpp \
	src/opengl/drawable/mesh.cpp \
	src/opengl/drawable/billboard.cpp \
	src/opengl/drawable/framebuffer.cpp \
	src/window/input.cpp \
	src/engine/parsers/gltf.cpp \
	src/engine/parsers/png.cpp \
	src/engine/runtime/framepacer.cpp \
	src/engine/runtime/texturemap.cpp \
	src/engine/runtime/renderer.cpp \
	src/engine/scene/model.cpp \
	src/engine/scene/gizmo.cpp \
	src/engine/scene/lamp.cpp \
	src/engine/scene/scene.cpp \
	src/engine/scene/camera.cpp \
	src/main.cpp

C_SRCS = \
	$(EXTERN)/glad/glad.c

CPP_OBJS = $(CPP_SRCS:%.cpp=build/%.o)

C_OBJS   = $(C_SRCS:%.c=build/%.o)

OBJS     = $(CPP_OBJS) $(C_OBJS)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/src

clean-all:
	rm -rf build

.PHONY: all clean clean-all
