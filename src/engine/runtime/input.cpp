#include "input.h"

Input::Input(GLFWwindow *windowPtr)
{
    this->windowPtr = windowPtr;
}

void Input::Update(Viewport &viewport, const float &dt, Light &light)
{
	// Closes the window
	if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(windowPtr, GLFW_TRUE);
    }

	// Basic movement
	// Forward and back, along Z from camera's pov.
	if (glfwGetKey(windowPtr, GLFW_KEY_E) == GLFW_PRESS)
	{
		viewport.AddPosition(viewport.GetLocalAxis({0.0f, 0.0f, -1.0f}) * dt);
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS)
	{
		viewport.AddPosition(viewport.GetLocalAxis({0.0f, 0.0f, 1.0f}) * dt);
	}
	// Left and right, along X from camera's pov.
	if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS)
	{
		viewport.AddPosition(viewport.GetLocalAxis({-1.0f, 0.0f, 0.0f}) * dt);
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_F) == GLFW_PRESS)
	{
		viewport.AddPosition(viewport.GetLocalAxis({1.0f, 0.0f, 0.0f}) * dt);
	}
	// Up and down, along Y from world space.
	if (glfwGetKey(windowPtr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		viewport.AddPosition(viewport.GetLocalAxis({0.0f, 1.0f, 0.0f}) * dt);
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		viewport.AddPosition(viewport.GetLocalAxis({0.0f, -1.0f, 0.0f}) * dt);
	}

	// Rotation
	if (glfwGetKey(windowPtr, GLFW_KEY_I) == GLFW_PRESS)
	{
		viewport.AddRotation({movementSpeed * dt, 0.0f, 0.0f}); // pitch up
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_K) == GLFW_PRESS)
	{
		viewport.AddRotation({-movementSpeed * dt, 0.0f, 0.0f}); // pitch down
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_J) == GLFW_PRESS)
	{
		viewport.AddRotation({0.0f, movementSpeed * dt, 0.0f}); // yaw left
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_L) == GLFW_PRESS)
	{
		viewport.AddRotation({0.0f, -movementSpeed * dt, 0.0f}); // yaw right
	}
		if (glfwGetKey(windowPtr, GLFW_KEY_U) == GLFW_PRESS)
	{
		viewport.AddRotation({0.0f, 0.0f, movementSpeed * dt}); // yaw left
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_O) == GLFW_PRESS)
	{
		viewport.AddRotation({0.0f, 0.0f, -movementSpeed * dt}); // yaw right
	}

	// Resetters
	if (glfwGetKey(windowPtr, GLFW_KEY_H) == GLFW_PRESS)
	{
		viewport.SetPosition({-9.3,3.1,9.3});
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_G) == GLFW_PRESS)
	{
		viewport.SetRotation({0,315,0});
	}

	// Mouse input	
	if (glfwGetMouseButton(windowPtr, GLFW_MOUSE_BUTTON_RIGHT)) {
		glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	} else {
		glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

}
