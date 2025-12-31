#ifndef CAMERA_H
#define CAMERA_H

#include <opengl/shader.h>

#include <glad/glad.h>
#include <glfw/window.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera {
    public:

        int width;
        int hieght;
        float speed;
        float sensitivty;
        glm::vec3 Position;
        glm::vec3 Orientation;
        glm::vec3 Up;

        Camera(int width, int height, glm::vec3 position);
        void Matrix(float FOVdeg, float nearPLane, float farPLane, Shader& shader, const char* uniform);
        void Inputs(GLFWwindow* window);

};
#endif