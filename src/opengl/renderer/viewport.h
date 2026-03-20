#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <opengl/pipeline/shader.h>

#include <glad/glad.h>
#include <window/window.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

// #include "opengl/buffers/ubo.h"

class Viewport
{
public:
	// Camera constructor to set up initial values
	Viewport(int width, int height, glm::vec3 position, glm::vec3 orientation);
	// Updates and exports the camera matrix to the Vertex Shader
	void updateCameraMatrix(
		float FOVdeg,
		float nearPlane,
		float farPlane
	);
	void linkCameraMatrix(const Shader& shader, const char* uniform) const;

	void linkCameraPos(const Shader& shader, const char* uniform) const;

	void Inputs(GLFWwindow* window);

	glm::vec3 position;
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);

private:
	// Stores the width and height of the window
	int fbWidth;
	int fbHeight;
	// Stores the main vectors of the camera

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.f);
	
	float pitch = 0.f;
	float yaw = -90.f;
	float sensitivity = 0.03f; // this default value is nice
	bool firstClick = true;

	float speed = 1.0f;
};

#endif