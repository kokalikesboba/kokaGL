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

glm::mat4 Camera::GetCameraMatrix(int fbWidth, int fbHeight) const
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
    return MatrixOps::RotationInverseMatrix(orientation);
}

Camera::~Camera()
{
    // Intentionally left blank
}
