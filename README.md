# kokaGL 
kokaGL is a cross-platform rendering library that is designed with expandability in mind. Right now it uses an OpenGL 4.1 rendering backend, with Vulkan being researched.

(Author's note: I use this project as a learning platform for software development and rendering architecture. This project is the successor to [koka3d](https://github.com/kokalikesboba/koka3D))

<img width="400" height="400" alt="Image" src="https://github.com/user-attachments/assets/326000a6-cd83-44fa-8741-7a57d06d14a8" />
<img width="400" height="400" alt="Image" src="https://github.com/user-attachments/assets/3a9ee5b2-d807-4f59-8a3b-3e41fd3bcfa5" />

## Core Features
 - Windows, Mac, Linux as supported platforms.
 - User defined Scene loading with JSON at runtime.
 - glTF 2.1 model parsing according to it's core specs.
 - Deltatime implementation with variable window refresh rate.
 - Viewport manipulation with trackpad support.
 - Material support for a PBR pipline

### OpenGL Renderer Features
 - User defined JSON renderer configuration,
 - Key-valued texture uploads to GPU to save memory.
 - Framebuffer tand GLSL post processing.
 - Blinn-phong shading with support for a PBR pipline.

## Compiling

kokaGL requires OpenGL 4.1 for compilation and runtime.

kokaGL requires a glfw3 package equivalent installed on the system for compilation.

CMake can be used to compile this project provided the previous requirements are met.

## Documentation
Documentation, design goals, examples can be found at the [kokaGL wiki](https://github.com/kokalikesboba/kokaGL/wiki).
