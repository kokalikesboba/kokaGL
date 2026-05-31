#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <opengl/resources/shader.h>

#include <glad/glad.h>
#include <window/window.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>	
#include <glm/gtx/vector_angle.hpp>

// #include "opengl/buffers/ubo.h"

class Viewport
{
public:

	Viewport(int width, int height);
	
	void SetPosition(glm::vec3 position);
	void AddPosition(glm::vec3 position);
	glm::vec3 GetPosition() const;
	glm::mat4 GetPositionInverseMatrix() const;

	void SetEulerRotation(glm::vec3 rotation);
	void AddEulerRotation(glm::vec3 rotation);
	void SetOrientation(glm::quat orientation);
	glm::quat GetOrientation() const;

	glm::mat4 GetRotationInverseMatrix() const;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetViewportMatrix() const;

	glm::vec3 GetLocalAxis(glm::vec3 axis);

	void LinkViewportMatrix(const Shader& shader, const char* uniform) const;
	// TODO: This was made for a point light shader and it's not a great name, there are better ways to do this.
	void LinkViewportPos(const Shader& shader, const char* uniform) const;
	
private:
	// Something upstream gone wrong if this size ends up on screen
	float fbWidth = 1000.f;
	float fbHeight = 1000.f;
	float aspect = 1.f;

	glm::vec3 position = {0.f, 0.f, 0.f};
	// identity quat
	glm::quat orientation = {1.f, 0.f, 0.f, 0.f};

	float nearPlane = 0.1f;
	float farPlane = 100.f;
	float eulerFOV = 70.f;
};

#endif