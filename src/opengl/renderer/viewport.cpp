#include "viewport.h"

Viewport::Viewport(int width, int height, glm::vec3 position, glm::vec3 orientation)
{
	fbWidth = width;
	fbHeight = height; 
	this->position = position;
	this->orientation = orientation;
	glViewport(0,0,fbWidth,fbHeight);
}

void Viewport::updateCameraMatrix(float FOVdeg, float nearPlane, float farPlane)
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

void Viewport::linkCameraMatrix(const Shader &shader, const char *uniform) const
{
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.getID(), uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Viewport::linkCameraPos(const Shader &shader, const char *uniform) const
{
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.getID(), uniform), position.x, position.y, position.z);
}