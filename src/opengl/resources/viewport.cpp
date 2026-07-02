#include "viewport.h"

Viewport::Viewport(int fbWidth, int fbHeight)
{
	this->fbWidth = fbWidth;
	this->fbHeight = fbHeight;

	glViewport(0,0,fbWidth,fbHeight);
}

glm::mat4 Viewport::GetPositionInverseMatrix() const
{
    glm::mat4 inversePos = glm::translate(glm::mat4(1.0f),-position);
	return inversePos;
}

glm::mat4 Viewport::GetRotationInverseMatrix() const
{
	glm::mat4 inverseRotation = glm::mat4_cast(glm::conjugate(orientation));
    return inverseRotation;
}

glm::mat4 Viewport::GetViewMatrix() const
{
	glm::mat4 viewMatrix = GetRotationInverseMatrix() * GetPositionInverseMatrix();
	return viewMatrix;
}

glm::mat4 Viewport::GetProjectionMatrix() const
{
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(eulerFOV), fbWidth/fbHeight, nearPlane, farPlane);
	return projectionMatrix;
}

glm::mat4 Viewport::GetViewportMatrix() const
{
	glm::mat4 viewportMatrix = GetProjectionMatrix() * GetViewMatrix();
    return viewportMatrix;
}