#include "transform.h"

void Transform::SetPosition(glm::vec3 position)
{
	this->position = position;
}

void Transform::AddPosition(glm::vec3 position)
{
	this->position += position;
}

glm::vec3 Transform::GetPosition() const
{
    return position;
}

void Transform::SetEulerRotation(glm::vec3 rotation)
{
    glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    orientation = qYaw * qPitch * qRoll;
}

void Transform::SetOrientation(glm::quat orientation)
{
	this->orientation = orientation;
}

void Transform::AddEulerRotation(glm::vec3 rotation)
{
	glm::quat qPitch = glm::angleAxis(glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat qYaw = glm::angleAxis(glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat qRoll = glm::angleAxis(glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::quat delta = qYaw * qPitch * qRoll;
	orientation *=  delta;
}

glm::quat Transform::GetOrientation() const
{
    return orientation;
}
