#include "input.h"

Input::Input(GLFWwindow *windowPtr)
{
    this->windowPtr = windowPtr;
}

void Input::Update(Viewport &viewport, const float &dt, Light &light)
{

	glfwSetWindowUserPointer(windowPtr, this);
	glfwSetScrollCallback(windowPtr, [](GLFWwindow* w, double x, double y) {
		Input* input = static_cast<Input*>(glfwGetWindowUserPointer(w));
		input->scrollX = x;
	});

	// Closes the window
	if (glfwGetKey(windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(windowPtr, GLFW_TRUE);
    }

	// Basic movement
	// Forward and back, along Z from camera's pov.
	if (glfwGetKey(windowPtr, GLFW_KEY_E) == GLFW_PRESS)
	{
		viewport.AddPosition(viewport.GetLocalAxis({0.0f, 0.0f, -1.0f}) * dt * movementSpeed);
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS)
	{
		viewport.AddPosition(viewport.GetLocalAxis({0.0f, 0.0f, 1.0f}) * dt * movementSpeed);
	}
	// Left and right, along X from camera's pov.
	if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS)
	{
		viewport.AddPosition(viewport.GetLocalAxis({-1.0f, 0.0f, 0.0f}) * dt * movementSpeed);
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_F) == GLFW_PRESS)
	{
		viewport.AddPosition(viewport.GetLocalAxis({1.0f, 0.0f, 0.0f}) * dt * movementSpeed);
	}
	// Up and down, along Y from world space.
	if (glfwGetKey(windowPtr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		viewport.AddPosition(glm::vec3{0.0f, 1.0f, 0.0f} * dt * movementSpeed);
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		viewport.AddPosition(glm::vec3{0.0f, -1.0f, 0.0f} * dt * movementSpeed);
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

	if (scrollX != 0.0) {
		std::cout << "Trackpad input detected! :D" << std::endl;
		trackpadMode = true;
		scrollX = 0.0f;
	}

		// Mouse input	
	if (glfwGetMouseButton(windowPtr, GLFW_MOUSE_BUTTON_RIGHT)) {
		// If you don't add this for Wayland, it doesn't hide the cursor most of the time.
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
		viewport.SetRawRotation(qYaw * viewport.GetRotation() * qPitch);
	} else {
		glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}

}
