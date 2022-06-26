#include "Camera.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Engine
{
    Camera::Camera(float left, float right, float bottom, float top)
    {
        this->projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        this->viewMatrix = glm::mat4(1.0f);
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

    void Camera::SetProjectionMatrix(float left, float right, float bottom, float top)
    {
        this->projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

    void Camera::Update()
    {
        glm::mat4 transform = translate(glm::mat4(1.0f), position) *
            rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));
        viewMatrix = inverse(transform);
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }
}
