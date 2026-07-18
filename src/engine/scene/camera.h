#ifndef CAMERA_H
#define CAMERA_H

#include "math/matrixops.hpp"
#include "math/transform.h"

class Camera : public Transform
{
public:
    using Transform::SetPosition;
	using Transform::AddPosition;
	using Transform::GetPosition;

	using Transform::SetOrientation;
	using Transform::GetOrientation;
	using Transform::SetEulerRotation;
	using Transform::AddEulerRotation;
	using Transform::GetEulerRotation;
	using Transform::GetLocalAxis;
	using Transform::GetForwardAxis;

    Camera();
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);
	void SetFOV(float eulerFOV);
    glm::mat4 GetCameraMatrix(int fbWidth, int fbHeight) const;
    glm::mat4 GetRotationMatrix() const;
    ~Camera();

private:
	float eulerFOV = 70.f;
	float fbWidth = 0.f;
	float fbHeight = 0.f;
	float nearPlane = 0.1f;
	float farPlane = 100.f;
};

#endif 