#include "viewport.h"

Viewport::Viewport(int width, int height, glm::vec3 position, glm::vec3 orientation)
{
	fbWidth = width;
	fbHeight = height; 
	SetPosition(position);
	SetOrientation(orientation);
	glViewport(0,0,fbWidth,fbHeight);
}

void Viewport::UpdateCameraMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	viewMatrix = glm::lookAt(position, position + orientation, up);
	// Adds perspective to the scene
	projectionMatrix = glm::perspective(glm::radians(FOVdeg), (float)fbWidth / fbHeight, nearPlane, farPlane);

	cameraMatrix = projectionMatrix * viewMatrix; 
}

void Viewport::LinkCameraMatrix(const Shader &shader, const char *uniform) const
{
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Viewport::LinkCameraPos(const Shader &shader, const char *uniform) const
{
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.getID(), uniform), position.x, position.y, position.z);
}

void Viewport::SetPosition(glm::vec3 position)
{
	this->position += position;
}

void Viewport::SetOrientation(glm::vec3 rotation)
{
    glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    glm::quat combined = qYaw * qPitch * qRoll;
    orientation = glm::normalize(glm::vec3(combined * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)));
}
