#include "input.h"

Input::Input(Window& window) : window(window)
{
    this->windowPtr = window.GetWindowPtr();
}

void Input::Update(Camera& camera, const float dt)
{
	// Trackpad input, accumulated by Window since last frame.
	double scrollX, scrollY;
	window.ConsumeScroll(scrollX, scrollY);
	if (scrollX != 0.0) {
		trackpadMode = true;
	}

	if (trackpadMode) {
		float yaw = -scrollX * trackpadSensitivity;
		float pitch = -scrollY * trackpadSensitivity;
		glm::quat qYaw = glm::angleAxis((float)yaw, glm::vec3(0.f,1.f,0.f));
		glm::quat qPitch = glm::angleAxis((float)pitch, glm::vec3(1.f,0.f,0.f));
		camera.SetOrientation(qYaw * camera.GetOrientation() * qPitch);
	}
		// Mouse input	
	if (glfwGetMouseButton(windowPtr, GLFW_MOUSE_BUTTON_RIGHT) && (!trackpadMode)) {
		glfwFocusWindow(windowPtr);
		glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (firstClick) {
			firstClick = false;
			glfwSetCursorPos(windowPtr, 0.f, 0.f);
			cursorHistory.clear();
		}

		glfwGetCursorPos(windowPtr, &cursorPos.x, &cursorPos.y);
		cursorHistory.push_front(cursorPos);
		if (cursorHistory.size() < 2) {
			return;
		} else if (cursorHistory.size() >= maxHistory) {
			cursorHistory.pop_back();
		}
		glm::dvec2 cursorDelta = cursorHistory[1] - cursorHistory[0];
		
		float yaw = cursorDelta.x * sensitivity;
		float pitch = cursorDelta.y * sensitivity;
		glm::quat qYaw = glm::angleAxis((float)yaw, glm::vec3(0.f,1.f,0.f));
		glm::quat qPitch = glm::angleAxis((float)pitch, glm::vec3(1.f,0.f,0.f));
		camera.SetOrientation(qYaw * camera.GetOrientation() * qPitch);
	} else {
		glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}

	// Closes the window
	if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(windowPtr, GLFW_TRUE);
    }

	// Basic movement
	// Forward and back, along Z from camera's pov.
	if (glfwGetKey(windowPtr, GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.AddPosition(camera.GetLocalAxis({0.0f, 0.0f, -1.0f}) * dt * movementSpeed);
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.AddPosition(camera.GetLocalAxis({0.0f, 0.0f, 1.0f}) * dt * movementSpeed);
	}
	// Left and right, along X from camera's pov.
	if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.AddPosition(camera.GetLocalAxis({-1.0f, 0.0f, 0.0f}) * dt * movementSpeed);
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_F) == GLFW_PRESS)
	{
		camera.AddPosition(camera.GetLocalAxis({1.0f, 0.0f, 0.0f}) * dt * movementSpeed);
	}
	// Up and down, along Y from world space.
	if (glfwGetKey(windowPtr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.AddPosition(glm::vec3{0.0f, 1.0f, 0.0f} * dt * movementSpeed);
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camera.AddPosition(glm::vec3{0.0f, -1.0f, 0.0f} * dt * movementSpeed);
	}

	// Rotation
	if (glfwGetKey(windowPtr, GLFW_KEY_I) == GLFW_PRESS)
	{
		camera.AddEulerRotation({movementSpeed * dt, 0.0f, 0.0f}); // pitch up
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_K) == GLFW_PRESS)
	{
		camera.AddEulerRotation({-movementSpeed * dt, 0.0f, 0.0f}); // pitch down
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_J) == GLFW_PRESS)
	{
		camera.AddEulerRotation({0.0f, movementSpeed * dt, 0.0f}); // yaw left
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_L) == GLFW_PRESS)
	{
		camera.AddEulerRotation({0.0f, -movementSpeed * dt, 0.0f}); // yaw right
	}
		if (glfwGetKey(windowPtr, GLFW_KEY_U) == GLFW_PRESS)
	{
		camera.AddEulerRotation({0.0f, 0.0f, movementSpeed * dt}); // yaw left
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_O) == GLFW_PRESS)
	{
		camera.AddEulerRotation({0.0f, 0.0f, -movementSpeed * dt}); // yaw right
	}

	// Resetters
	if (glfwGetKey(windowPtr, GLFW_KEY_H) == GLFW_PRESS)
	{
		camera.SetEulerRotation({0,0,0});
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_G) == GLFW_PRESS)
	{
		camera.SetEulerRotation({0,0,0});
	}
}
