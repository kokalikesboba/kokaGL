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

// TODO: Input should be handled with it's own class. 
void Viewport::Inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * -glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * -orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(orientation, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		position += speed * -up;
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		fbWidth += 5.f; 
	}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		fbWidth -= 5.f; 
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		fbHeight += 5.f; 
	}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		fbHeight -= 5.f; 
	}



	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		double cursorPosX, cursorPosY;
		if (glfwRawMouseMotionSupported()) {
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			std::cout << "raw mouse motion enabled" << std::endl;
			glfwGetCursorPos(window,&cursorPosX, &cursorPosY);
		}
		// Hides cursor because Wayland doesn't hide on disable
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		// Disables required to get raw mouse input
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		std::cout << cursorPosX << " " << cursorPosY << std::endl;
		glfwSetCursorPos(window,0.f,0.f);

		// TODO: needs method
		orientation += glm::vec3(cursorPosX * 0.001f, cursorPosY * -0.001f, 0);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}