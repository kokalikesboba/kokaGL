#include "viewport.h"

Viewport::Viewport(int fbWidth, int fbHeight)
{
	this->fbWidth = fbWidth;
	this->fbHeight = fbHeight;

	glViewport(0,0,fbWidth,fbHeight);
}

void Viewport::SetPosition(glm::vec3 position)
{
	this->position = position;
}

void Viewport::AddPosition(glm::vec3 position)
{
	this->position += position;
}

glm::vec3 Viewport::GetPosition() const
{
    return position;
}

glm::mat4 Viewport::GetPositionInverseMatrix() const
{
    glm::mat4 inversePos = glm::translate(glm::mat4(1.0f),-position);
	return inversePos;
}

void Viewport::SetRotation(glm::vec3 eulerRotation)
{
    glm::quat qPitch = glm::angleAxis(glm::radians(eulerRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat qYaw = glm::angleAxis(glm::radians(eulerRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat qRoll = glm::angleAxis(glm::radians(eulerRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    orientation = qYaw * qPitch * qRoll;
}

void Viewport::SetRawRotation(glm::quat orientation)
{
	this->orientation = orientation;
}

void Viewport::AddRotation(glm::vec3 eulerRotation)
{
	glm::quat qPitch = glm::angleAxis(glm::radians(eulerRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat qYaw = glm::angleAxis(glm::radians(eulerRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat qRoll = glm::angleAxis(glm::radians(eulerRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::quat delta = qYaw * qPitch * qRoll;
	orientation *=  delta;
}

glm::quat Viewport::GetRotation() const
{
    return orientation;
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

glm::vec3 Viewport::GetLocalAxis(glm::vec3 axis)
{
    return orientation * glm::normalize(axis);
}

void Viewport::LinkViewportMatrix(const Shader &shader, const char *uniform) const
{
	shader.Activate();
	glm::mat4 viewportMatrix = GetViewportMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), uniform), 1, GL_FALSE, glm::value_ptr(viewportMatrix));
}

void Viewport::LinkViewportPos(const Shader &shader, const char *uniform) const
{
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.getID(), uniform), position.x, position.y, position.z);
}

