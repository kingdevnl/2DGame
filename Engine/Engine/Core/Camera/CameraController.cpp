#include "CameraController.hpp"

#include "Core/Input/Keyboard.hpp"
#include "Core/Util/Math.hpp"

namespace Engine
{
    CameraController::CameraController(float aspectRatio)
    {
        this->aspectRatio = aspectRatio;
        this->zoomLevel = 1.0;
        this->position = glm::vec3(0.0, 0.0, 0.0);
        this->camera = Camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    }


    void CameraController::OnMouseScroll(Events::MouseScrollEvent& e)
    {
        this->zoomLevel -= static_cast<float>(e.yOffset) * 0.2f;
        this->zoomLevel = Math::Clamp(this->zoomLevel, 0.1f, 4.0f);
        UpdateCamera();
    }

    void CameraController::OnWindowResize(Events::WindowResizeEvent& e)
    {
        this->aspectRatio = static_cast<float>(e.width) / static_cast<float>(e.height);
        UpdateCamera();
    }

    void CameraController::UpdateCamera()
    {
        camera.SetProjectionMatrix(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    }

    void CameraController::OnUpdate(float dt)
    {
        using Input::IsKeyDown;

         const float cameraSpeed = 1.8f * zoomLevel;


        if (IsKeyDown(GLFW_KEY_LEFT) || IsKeyDown(GLFW_KEY_A))
            position.x -= dt * cameraSpeed;

       else if (IsKeyDown(GLFW_KEY_RIGHT) || IsKeyDown(GLFW_KEY_D))
            position.x += dt * cameraSpeed;

        if (IsKeyDown(GLFW_KEY_DOWN) || IsKeyDown(GLFW_KEY_S))
            position.y -= dt * cameraSpeed;

        else if (IsKeyDown(GLFW_KEY_UP) || IsKeyDown(GLFW_KEY_W))
            position.y += dt * cameraSpeed;


        this->camera.SetPosition(this->position);
    }

    void CameraController::OnEvent(Event& event)
    {
        switch (event.type)
        {
        case EventType::WINDOW_RESIZE_EVENT:
            OnWindowResize(static_cast<Events::WindowResizeEvent&>(event));
            break;

        case EventType::MOUSE_SCROLL_EVENT:
            OnMouseScroll(static_cast<Events::MouseScrollEvent&>(event));
            break;

        default: break;
        }
    }
}
