#include "CameraController.hpp"

#include "Engine/Core/Input/Keyboard.hpp"
#include "Engine/Core/Util/Math.hpp"

namespace Engine
{

    CameraController::CameraController(float aspectRatio)
    {
        this->aspectRatio = aspectRatio;
        this->zoomLevel = 1.0;
        this->position = glm::vec3(0.0, 0.0, 0.0);
        this->camera = Camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    }


    bool CameraController::OnMouseScroll(MouseScrollEvent& event)
    {
        this->zoomLevel -= static_cast<float>(event.yOffset) * 0.2f;
        this->zoomLevel = Math::Clamp(this->zoomLevel, 0.1f, 4.0f);
        UpdateCamera();
        return true;
    }

    bool CameraController::OnWindowResize(WindowResizeEvent& event)
    {
        spdlog::info("Window resized to {}x{}", event.width, event.height);
        this->aspectRatio = static_cast<float>(event.width) / static_cast<float>(event.height);
        UpdateCamera();
        return true;
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
            EventDispatcher dispatcher(event);
            dispatcher.Dispatch<MouseScrollEvent>(BIND_EVENT_FN(CameraController::OnMouseScroll));
            dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(CameraController::OnWindowResize));
    }
}
