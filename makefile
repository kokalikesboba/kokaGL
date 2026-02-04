EXTERN = extern


# =======================
# COMPILERS
# =======================

# C++ compiler
CXX = g++

# C compiler (used for glad.c)
CC  = gcc


# =======================
# COMPILER FLAGS
# =======================

# Flags for compiling C++ source files (.cpp)
# -g        : include debug symbols
# -O2       : enable optimization (still fine for debugging)
# -std=c++17: use the C++17 standard
# -I...     : directories to search for #include "..."
CXXFLAGS = -g -O2 -std=c++17 -I$(EXTERN) -I$(EXTERN)/KHR -I$(EXTERN)/imgui -Isrc

# Flags for compiling C source files (.c)
CFLAGS   = -g -O2 -I$(EXTERN) -I$(EXTERN)/KHR -I$(EXTERN)/imgui -Isrc


# =======================
# LINKER FLAGS
# =======================

# Libraries to link against when creating the final executable
# These are ONLY used in the final link step
LDLIBS   = -lglfw -lGL -ldl -lassimp


# =======================
# OUTPUT
# =======================

# Name of the final executable
TARGET = kokaGL


# =======================
# SOURCE FILES
# =======================

# All C++ source files in the project
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
	src/opengl/pipeline/texture.cpp \
	src/opengl/pipeline/shader.cpp \
	src/opengl/renderer/viewport.cpp \
	src/opengl/renderer/mesh.cpp \
	src/entities/model.cpp \
	src/entities/light.cpp \
	src/main.cpp

# All C source files in the project
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
	$(CXX) $(OBJS) -o $(TARGET) $(LDLIBS)


# =======================
# COMPILE C++ FILES
# =======================

# Pattern rule:
#   build/anything.o depends on anything.cpp
build/%.o: %.cpp
	# Create the output directory if it doesn't exist
	@mkdir -p $(dir $@)

	# Compile ONE .cpp file into ONE .o file
	# $< = input source file
	# $@ = output object file
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