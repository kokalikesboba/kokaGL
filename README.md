# koka-runtime 
This project supersedes [koka3d](https://github.com/kokalikesboba/koka3D). It is a graphics runtime that is designed for data modularity and safety. Right now it uses OpenGL 4.1, Vulkan is being researched.

You can find design goals, quirks, and documentations on the [wiki](https://github.com/kokalikesboba/koka-runtime/wiki) tab.

<img width="400" height="416" alt="Image" src="https://github.com/user-attachments/assets/326000a6-cd83-44fa-8741-7a57d06d14a8" />

# Features:
- JSON model loading at runtime.
- GLTF parsing according to it's core specification.
- Viewport manipulation with trackpad support.
- Deltatime implementation.
- Variable window refresh rate.
- Deduplicated texture uploads on GPU.
- Framebuffers and GLSL post processing.
- Blinn-phong shading, a partial PBR pipline.
- Mesh and billboard loading.

# Installation

### You must have an OpenGL 4.1 capable GPU.

Included are Visual Studio Code profiles that work on Ubuntu 25.04 and MacOS Tahoe. Regardless of if you wish to use them or not, you must have the following packages installed system wide to build with `make`.

- `Clang`
- `GLFW 3.4`

Use `brew` or `apt` for them.

Additionally, if you wish you use the VSCode profiles, you must  install the `CodeLLDB` extension since this is the expected debugger.

Other dependencies such as GLAD, glm, stb, ImGUI, simdjson, fastgltf, are vendored in this repository under the `extern/` directory and require no further installation.
