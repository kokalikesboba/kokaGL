EXTERN = extern
# =======================
# COMPILERS
# =======================
CXX = clang++
CC  = clang
# =======================
# COMPILER FLAGS
# =======================
CXXFLAGS = -g -O2 -std=c++17 -I$(EXTERN) -I$(EXTERN)/KHR -I$(EXTERN)/imgui -Isrc
CFLAGS   = -g -O2 -I$(EXTERN) -I$(EXTERN)/KHR -I$(EXTERN)/imgui -Isrc
# =======================
# PLATFORMS
# =======================
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    CXXFLAGS += -I/opt/homebrew/include
    CFLAGS   += -I/opt/homebrew/include
    LDLIBS    = -lglfw -lassimp -framework OpenGL
    LDFLAGS  += -L/opt/homebrew/lib
else
    LDLIBS    = -lglfw -lGL -ldl -lassimp
endif
# =======================
# OUTPUT
# =======================
TARGET = kokaGL
# =======================
# SOURCE FILES
# =======================
CPP_SRCS = \
	$(EXTERN)/stb/stb.cpp \
	$(EXTERN)/imgui/imgui.cpp \
	$(EXTERN)/imgui/imgui_draw.cpp \
	$(EXTERN)/imgui/imgui_tables.cpp \
	$(EXTERN)/imgui/imgui_widgets.cpp \
	$(EXTERN)/imgui/imgui_demo.cpp \
	$(EXTERN)/imgui/backends/imgui_impl_glfw.cpp \
	$(EXTERN)/imgui/backends/imgui_impl_opengl3.cpp \
	src/window/window.cpp \
	src/opengl/buffers/vao.cpp \
	src/opengl/buffers/vbo.cpp \
	src/opengl/buffers/ebo.cpp \
	src/opengl/buffers/ubo.cpp \
	src/opengl/buffers/fbo.cpp \
	src/opengl/resources/texture.cpp \
	src/opengl/resources/shader.cpp \
	src/opengl/resources/viewport.cpp \
	src/opengl/drawable/mesh.cpp \
	src/opengl/drawable/framebuffer.cpp \
	src/engine/components/model.cpp \
	src/engine/components/light.cpp \
	src/engine/runtime/input.cpp \
	src/engine/runtime/framepacer.cpp \
	src/engine/runtime/texturepool.cpp \
	src/engine/runtime/parser.cpp \
	src/main.cpp


C_SRCS = \
	$(EXTERN)/glad/glad.c


# =======================
# OBJECT FILES
# =======================

# Convert each .cpp file into a corresponding .o file in build/
# Example:
#   src/main.cpp  -> build/src/main.o
CPP_OBJS = $(CPP_SRCS:%.cpp=build/%.o)

# Convert each .c file into a corresponding .o file in build/
# Example:
#   libs/glad/glad.c -> build/libs/glad/glad.o
C_OBJS   = $(C_SRCS:%.c=build/%.o)

# Combine all object files into one list
OBJS     = $(CPP_OBJS) $(C_OBJS)


# =======================
# DEFAULT TARGET
# =======================

# This is what runs when you type `make`
all: $(TARGET)


# =======================
# LINK STEP
# =======================

# The final executable depends on ALL object files
# If any .o file changes, this rule runs
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS) $(LDLIBS)


# =======================
# COMPILE C++ FILES
# =======================

# Pattern rule:
#   build/anything.o depends on anything.cpp
build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# =======================
# COMPILE C FILES
# =======================

# Same as above, but for .c files
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


# =======================
# CLEANUP
# =======================

# Remove all build output
# Run with: make clean
clean:
	rm -rf build


# =======================
# PHONY TARGETS
# =======================

# Tell make these targets are not actual files
.PHONY: all clean
