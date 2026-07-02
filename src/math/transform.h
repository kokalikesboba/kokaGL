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

	void SetEulerRotation(glm::vec3 rotation);
	void AddEulerRotation(glm::vec3 rotation);
	void SetOrientation(glm::quat orientation);
	glm::quat GetOrientation() const;
protected:
	glm::vec3 position = {0.f, 0.f, 0.f};
	// identity quat
	glm::quat orientation = {1.f, 0.f, 0.f, 0.f};
};

#endif