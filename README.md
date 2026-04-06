This project supercedes koka3D in spirit. It is my first hardware accelerated renderer, it uses the OpenGL API. 
It started off following Victor Gordan's "LearnOpenGL" series, but it has greatly divereged in feature set, structure, and scope.

This repo contains development profiles for Visual Studio Code for Ubuntu 25.04 and MacOS Tahoe. 
To use them, you must have these dependencies installed:
Clang
CodeLLDB
GLFW 3.4 
AssImp 6.0.4

Personal notes.
This was the first project taught me a lot more about how to integrate external libraries into my project- I had a habit of trying to make my own matrix or parser libraries, but learned that this is a waste of time. 
I encountered ownership and lifetime issues- This is the first project where implementing class destructors actually made sense given OpenGL's global state. Many classes in this project are just OpenGL managed objects wrapped up for convenience.
Porting this project to MacOS was pretty straightforward, I mainly just had to switch to cross-platform available tooling and create another VSCode profile,
