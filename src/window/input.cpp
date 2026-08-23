#include "input.h"

Input::Input(Window& window) : window(window)
{
}

void Input::Update(Camera& camera, const float dt)
{
	HandleMouseInput(camera, dt);
	HandleKeyboardInput(camera, dt);
}

void Input::HandleMouseInput(Camera &camera, const float dt)
{
	// Trackpad input, accumulated by Window since last frame.
	double scrollX = 0;
	double scrollY = 0;
	window.ConsumeScroll(scrollX, scrollY);
	if (scrollX != 0.0) {
		float yaw = -scrollX * trackpadSensitivity;
		float pitch = -scrollY * trackpadSensitivity;
		glm::quat qYaw = glm::angleAxis((float)yaw, glm::vec3(0.f,1.f,0.f));
		glm::quat qPitch = glm::angleAxis((float)pitch, glm::vec3(1.f,0.f,0.f));
		camera.SetOrientation(qYaw * camera.GetOrientation() * qPitch);
		return;
	}

	// Mouse input	
	if (glfwGetMouseButton(window.Get(), GLFW_MOUSE_BUTTON_RIGHT)) {
		glfwFocusWindow(window.Get());
		glfwSetInputMode(window.Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		if (firstClick) {
			firstClick = false;
			glfwSetCursorPos(window.Get(), 0.f, 0.f);
			cursorHistory.clear();
		}
		
		glfwGetCursorPos(window.Get(), &cursorPos.x, &cursorPos.y);
		cursorHistory.push_front(cursorPos);
		if (cursorHistory.size() <= 2) {
			return;
		} else if (cursorHistory.size() >= maxHistory) {
			cursorHistory.pop_back();
		}
		glm::dvec2 cursorDelta = cursorHistory[1] - cursorHistory[0];
		
		float yaw = cursorDelta.x * mouseSensitivity;
		float pitch = cursorDelta.y * mouseSensitivity;
		glm::quat qYaw = glm::angleAxis((float)yaw, glm::vec3(0.f,1.f,0.f));
		glm::quat qPitch = glm::angleAxis((float)pitch, glm::vec3(1.f,0.f,0.f));
		camera.SetOrientation(qYaw * camera.GetOrientation() * qPitch);
	} else {
		glfwSetInputMode(window.Get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}

void Input::HandleKeyboardInput(Camera &camera, const float dt)
{
	// Closes the window
	if (glfwGetKey(window.Get(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window.Get(), GLFW_TRUE);
    }

	// Basic movement
	// Forward and back, along Z from camera's pov.
	if (glfwGetKey(window.Get(), GLFW_KEY_E) == GLFW_PRESS)
	{
		camera.AddPosition(camera.GetLocalAxis({0.0f, 0.0f, -1.0f}) * dt * movementSpeed);
	}
	if (glfwGetKey(window.Get(), GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.AddPosition(camera.GetLocalAxis({0.0f, 0.0f, 1.0f}) * dt * movementSpeed);
	}
	// Left and right, along X from camera's pov.
	if (glfwGetKey(window.Get(), GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.AddPosition(camera.GetLocalAxis({-1.0f, 0.0f, 0.0f}) * dt * movementSpeed);
	}
	if (glfwGetKey(window.Get(), GLFW_KEY_F) == GLFW_PRESS)
	{
		camera.AddPosition(camera.GetLocalAxis({1.0f, 0.0f, 0.0f}) * dt * movementSpeed);
	}
	// Up and down, along Y from world space.
	if (glfwGetKey(window.Get(), GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.AddPosition(glm::vec3{0.0f, 1.0f, 0.0f} * dt * movementSpeed);
	}
	if (glfwGetKey(window.Get(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camera.AddPosition(glm::vec3{0.0f, -1.0f, 0.0f} * dt * movementSpeed);
	}

	// Rotation
	if (glfwGetKey(window.Get(), GLFW_KEY_I) == GLFW_PRESS)
	{
		camera.AddEulerRotation({movementSpeed * dt, 0.0f, 0.0f}); // pitch up
	}
	if (glfwGetKey(window.Get(), GLFW_KEY_K) == GLFW_PRESS)
	{
		camera.AddEulerRotation({-movementSpeed * dt, 0.0f, 0.0f}); // pitch down
	}
	if (glfwGetKey(window.Get(), GLFW_KEY_J) == GLFW_PRESS)
	{
		camera.AddEulerRotation({0.0f, movementSpeed * dt, 0.0f}); // yaw left
	}
	if (glfwGetKey(window.Get(), GLFW_KEY_L) == GLFW_PRESS)
	{
		camera.AddEulerRotation({0.0f, -movementSpeed * dt, 0.0f}); // yaw right
	}
		if (glfwGetKey(window.Get(), GLFW_KEY_U) == GLFW_PRESS)
	{
		camera.AddEulerRotation({0.0f, 0.0f, movementSpeed * dt}); // yaw left
	}
	if (glfwGetKey(window.Get(), GLFW_KEY_O) == GLFW_PRESS)
	{
		camera.AddEulerRotation({0.0f, 0.0f, -movementSpeed * dt}); // yaw right
	}

	// Resetters
	if (glfwGetKey(window.Get(), GLFW_KEY_H) == GLFW_PRESS)
	{
		camera.SetEulerRotation({0,0,0});
	}
	if (glfwGetKey(window.Get(), GLFW_KEY_G) == GLFW_PRESS)
	{
		camera.SetEulerRotation({0,0,0});
	}
}
