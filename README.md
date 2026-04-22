# KokaGL 
This project supersedes [koka3d](https://github.com/kokalikesboba/koka3D) in spirit. It is my first hardware accelerated renderer and it uses the OpenGL API. 

<img src="meta/readme_img1.png" width="250"/>

# Features:
- GLTF File Parsing and loading.
- Viewport manipulation.
- Variable window refresh rate.
- Framebuffers and GLSL post processing.
- Lambert Shading.
- Deltatime implementation.

# Installation

### You must have an OpenGL 3.3+ capable GPU.

Included are Visual Studio Code profiles that work on Ubuntu 25.04 and MacOS Tahoe. Regardless of if you wish to use them or not, you must have the following packages installed system wide to build with `make`.

- `Clang`
- `GLFW 3.4`
- `AssImp 6.0.4`

Use `brew` or `apt` for them.

Additionally, if you wish you use the VSCode profiles, you must  install `CodeLLDB` extension since this is the expected debugger.

Other dependencies such as GLAD, glm, stb, ImGUI, are already included in this repository under the `extern/` directory and require no further installation.

# Documentation / Personal Notes

### Libraries 

This was the first project taught me a lot more about how to integrate external libraries into my project. I had a habit of trying to make my own matrix or parser libraries, but quickly learned that this was a distraction from actually learning the graphics pipeline.

 - Since windowing is specific to platforms, GLFW3 is an external dependency. 

 - Since AssImp is a rather large library, it is an external dependency.

### Implementation

- I encountered ownership and lifetime issues- This is the first project where implementing class destructors actually made sense given OpenGL's global state. Many classes in this project are just OpenGL managed objects wrapped up for convenience.

### Platforms

- Porting this project to MacOS was pretty straightforward, I mainly just had to switch to cross-platform available tooling and create another VSCode profile.
