#ifndef UBO_H
#define UBO_H

#include "glad/glad.h"
#include "opengl/resources/shader.h"

#include <iostream>

class UBO
{
public:
	// Allocates an empty dynamic buffer of byteSize and binds it to the given slot.
	UBO(GLsizeiptr byteSize, GLuint slot);
	// Uploads a struct into the buffer. Struct layout must match the GLSL std140 block.
	template <typename T> void Update(const T& data);
	// Points a shader's named uniform block at this UBO's slot. Call once per shader (GL 3.3 has no binding= in GLSL).
	void LinkBlock(const Shader& shader, GLuint ID) const;
	void Bind() const;
	void Unbind() const;
	void Delete();
	~UBO();

	UBO(const UBO&) = delete;
	UBO& operator=(const UBO&) = delete;

private:
	GLuint ID = 0;
	GLuint slot = 0;
	GLsizeiptr byteSize = 0;
};

template <typename T>
inline void UBO::Update(const T& data)
{
	if (sizeof(T) != byteSize) {
		std::cerr << "[ERROR][UBO] Update called with " << sizeof(T)
			<< " bytes but buffer holds " << byteSize << std::endl;
		return;
	}
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(T), &data);
}

#endif
