#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "math/transform.h"
// TODO: Smell regarding viewport resizing
#include "glad/glad.h"

// is a 
class Viewport : public Transform
{
public:
	Viewport(int width, int height);
	glm::mat4 GetPositionInverseMatrix() const;
	glm::mat4 GetRotationInverseMatrix() const;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetViewportMatrix() const;
	glm::vec3 GetLocalAxis(glm::vec3 axis) const;
private:
	// Something upstream gone wrong if this size ends up on screen
	float fbWidth = 1000.f;
	float fbHeight = 1000.f;
	float aspect = 1.f;
	float nearPlane = 0.1f;
	float farPlane = 100.f;
	float eulerFOV = 70.f;
};

#endif