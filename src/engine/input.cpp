#include "input.h"

Input::Input(GLFWwindow *windowPtr)
{
    this->windowPtr = windowPtr;
}

void Input::Update(Viewport &viewport, const float &dt, Light &light)
{
	if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(windowPtr, GLFW_TRUE);
    }
    if (glfwGetKey(windowPtr, GLFW_KEY_I) == GLFW_PRESS) {
        light.Rotate({.01f, 0.0f, 0.f});
    }
    if (glfwGetKey(windowPtr, GLFW_KEY_K) == GLFW_PRESS) {
        light.Rotate({-.01f, 0.0f, 0.f});
    }
    if (glfwGetKey(windowPtr, GLFW_KEY_J) == GLFW_PRESS) {
        light.Rotate({0.0f, -.01f, 0.f});
    }
    if (glfwGetKey(windowPtr, GLFW_KEY_L) == GLFW_PRESS) {
        light.Rotate({0.0f, .01f, 0.f});
    }
    if (glfwGetKey(windowPtr, GLFW_KEY_APOSTROPHE) == GLFW_PRESS) {
        std::cout << "posx: " << viewport.position.x << std::endl;
        std::cout << "posy: " << viewport.position.y << std::endl;
        std::cout << "posz: " << viewport.position.z << std::endl;
        std::cout << "rotx: " << viewport.orientation.x << std::endl;
        std::cout << "roty: " << viewport.orientation.y << std::endl;
        std::cout << "rotz: " << viewport.orientation.z << std::endl;
    }
	if (glfwGetKey(windowPtr, GLFW_KEY_W) == GLFW_PRESS)
	{
		viewport.position += (movementSpeed * dt) * viewport.orientation;
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_A) == GLFW_PRESS)
	{
		viewport.position +=(movementSpeed * dt) * -glm::normalize(glm::cross(viewport.orientation, viewport.up));
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS)
	{
		viewport.position += (movementSpeed * dt) * -viewport.orientation;
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS)
	{
		viewport.position += (movementSpeed * dt) * glm::normalize(glm::cross(viewport.orientation, viewport.up));
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		viewport.position += (movementSpeed * dt) * viewport.up;
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		viewport.position += (movementSpeed * dt) * -viewport.up;
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		movementSpeed = 10.0f;
	}
	else if (glfwGetKey(windowPtr, GLFW_KEY_TAB) == GLFW_RELEASE)
	{
		movementSpeed = 10.f;
	}

	if (glfwGetKey(windowPtr, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		viewport.fbWidth += 5.f; 
	}
		if (glfwGetKey(windowPtr, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		viewport.fbWidth -= 5.f; 
	}

	if (glfwGetKey(windowPtr, GLFW_KEY_UP) == GLFW_PRESS)
	{
		viewport.fbHeight += 5.f; 
	}
		if (glfwGetKey(windowPtr, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		viewport.fbHeight -= 5.f; 
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_H) == GLFW_PRESS)
	{
		viewport.SetPosition({0.f,0.f,0.f});
	}

	// Handles mouse inputs
	if (glfwGetMouseButton(windowPtr, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{

		double cursorPosX, cursorPosY;

		if (glfwRawMouseMotionSupported()) {
			glfwSetInputMode(windowPtr, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
			glfwGetCursorPos(windowPtr,&cursorPosX, &cursorPosY);
		}
		// Bizarre Wayland workaround, both need to be enabled.
		glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		if(viewport.firstClick) {
			glfwSetCursorPos(windowPtr, 0.f, 0.f);
			cursorPosX = 0.f;
			cursorPosY = 0.f;
			viewport.firstClick = false;
		}

		viewport.yaw += (float)cursorPosX * viewport.sensitivity;
		viewport.pitch -= (float)cursorPosY * viewport.sensitivity;
		viewport.pitch = glm::clamp(viewport.pitch, -89.0f, 89.0f);

		// recompute orientation fresh every frame
   		viewport.orientation = glm::normalize(glm::vec3(
			cos(glm::radians(viewport.yaw)) * cos(glm::radians(viewport.pitch)),
			sin(glm::radians(viewport.pitch)),
			sin(glm::radians(viewport.yaw)) * cos(glm::radians(viewport.pitch))
    	));

		glfwSetCursorPos(windowPtr,0.f,0.f);

	}
	else if (glfwGetMouseButton(windowPtr, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		viewport.firstClick = true;
    }
}
