#include "camera.h"

Camera::Camera() {
    // Intentionally left blank
};

void Camera::SetNearPlane(float nearPlane)
{
    this->nearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
    this->farPlane = farPlane;
}

void Camera::SetFOV(float eulerFOV)
{
    this->eulerFOV = eulerFOV;
}
/*
glm::mat4 Camera::GetCameraMatrix() const
{
    return MatrixOps::PerspectiveView(
        eulerFOV,
        fbWidth,
        fbHeight,
        nearPlane,
        farPlane,
        position,
        orientation
    );
}

glm::mat4 Camera::GetRotationMatrix() const
{
    // return glm::mat4(glm::rotate(orientation));
}
*/
Camera::~Camera()
{
    // Intentionally left blank
}
