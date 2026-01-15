I started this project because I have been interested in graphics programming for the past year. It started off following Victor Gordan's "LearnOpenGL" series, but I've altered every class and have diverged in several places from his work.
This project is meant to be an evolution from koka3D and it is faster by a factor of at least 200.
So far, I have learned a little bit of how OpenGL's state machine works, obviously. But I also learned how to wrap library functions that make your main file look oh-so clean. 
This project has me thinking deeply about subtle performance tweaks- When is it appropriate to pass by value? When is it appropriate to pass by reference?
This was also first time that I encountered lifespan and ownership issues. My use of move-semantics is sparse, and to be honest I still don't quite understand them. But OpenGL's global resources are definitely a challenge I'm overcoming when it comes to class abstraction.
