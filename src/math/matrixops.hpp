#ifndef MATRIXOPS_HPP
#define MATRIXOPS_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"

// I chose to pass by value
namespace MatrixOps {
    inline glm::mat4 PositionInverseMatrix(glm::vec3 position)
    {
        glm::mat4 inversePos =
        glm::translate(glm::mat4(1.0f),-position);
        return inversePos;
    }

    inline glm::mat4 RotationInverseMatrix(glm::quat orientation)
    {
        glm::mat4 inverseRotation = 
        glm::mat4_cast(glm::conjugate(orientation));
        return inverseRotation;
    }

    inline glm::mat4 ViewMatrix(glm::vec3 position, glm::quat orientation)
    {
        glm::mat4 view = 
        RotationInverseMatrix(orientation) * PositionInverseMatrix(position);
        return view;
    }

    inline glm::mat4 PerspectiveMatrix(float eulerFOV, float fbWidth, float fbHeight, float nearPlane, float farPlane)
    {
        glm::mat4 perspective =
        glm::perspective(
            glm::radians(eulerFOV),
            fbWidth/fbHeight,
            nearPlane,
            farPlane
        );
        return perspective;
    }

    inline glm::mat4 OrthogonalMatrix(float left, float right, float bottom, float top, float near, float far) {
        glm::mat4 orthogonal = 
        glm::ortho(
            left,
            right,
            bottom,
            top,
            near, 
            far
        );
        return orthogonal;
    }

    inline glm::mat4 PerspectiveView(
        float eulerFOV,
        float fbWidth,
        float fbHeight,
        float nearPlane,
        float farPlane,
        glm::vec3 position,
        glm::quat orientation)
    {
        glm::mat4 perspectiveView = 
        PerspectiveMatrix(
            eulerFOV,
            fbWidth,
            fbHeight,
            nearPlane,
            farPlane
        ) * ViewMatrix(
            position,
            orientation
        );
        return perspectiveView;
    }

    inline glm::mat4 OrthogonalView(
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far,
        glm::vec3 position,
        glm::quat orientation) 
    {
        glm::mat4 orthogonalView = 
        OrthogonalMatrix (
            left,
            right,
            bottom,
            top,
            near,
            far
        ) * ViewMatrix(
            position,
            orientation
        );
        return orthogonalView;
    }
}

#endif