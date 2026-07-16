#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"

class Transform {
public:
	void SetPosition(glm::vec3 position);
	void AddPosition(glm::vec3 position);
	glm::vec3 GetPosition() const;

	void SetOrientation(glm::quat orientation);
	glm::quat GetOrientation() const;
	void SetEulerRotation(glm::vec3 rotation);
	void AddEulerRotation(glm::vec3 rotation);
	glm::vec3 GetEulerRotation() const;
	glm::vec3 GetLocalAxis(glm::vec3 axis) const;
	glm::vec3 GetForwardAxis() const;

	void SetScale(glm::vec3 scale);
	glm::vec3 GetScale() const;
protected:
	glm::vec3 up = {0.0, 1.f, 0.f};
	glm::vec3 position = {0.f, 0.f, 0.f};
	glm::quat orientation = {1.f, 0.f, 0.f, 0.f};
	glm::vec3 scale = {1.f, 1.f, 1.f};
};

#endif