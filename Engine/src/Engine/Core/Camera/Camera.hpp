#pragma once
#include "Engine/Engine.hpp"

namespace Engine
{
    class Camera
    {
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        float rotation = 0;

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 viewProjectionMatrix;


        void Update();

    public:
        Camera() = default;
        Camera(float left, float right, float bottom, float top);

        void SetPosition(const glm::vec3& pos)
        {
            position = pos;
            Update();
        }

        void SetRotation(float rot)
        {
            rotation = rot;
            Update();
        }


        void SetProjectionMatrix(float left, float right, float bottom, float top);

        glm::vec3& GetPosition() { return position; }
        float GetRotation() const { return rotation; }


        const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return viewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }
    };
}
