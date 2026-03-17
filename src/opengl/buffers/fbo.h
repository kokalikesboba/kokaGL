#ifndef FBO_H
#define FBO_H

#include <glad/glad.h>

#include <iostream>

class FBO {
    public:
        FBO();
        void Bind() const;
        void Unbind() const;
        void Delete();
        ~FBO();
    private:
        GLuint ID = 0;
};

#endif
