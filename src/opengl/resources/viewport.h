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
	void Resize(int width, int height);
	
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);
	void SetFOV(float eulerFOV);

	glm::mat4 GetPositionInverseMatrix() const;
	glm::mat4 GetRotationInverseMatrix() const;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
	glm::mat4 GetViewportMatrix() const;
private:
	float fbWidth = 0.f;
	float fbHeight = 0.f;
	float aspect = 0.f;

	float nearPlane = 0.1f;
	float farPlane = 100.f;
	float eulerFOV = 70.f;
};

#endif