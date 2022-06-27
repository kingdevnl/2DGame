#pragma once
#include "Camera.hpp"
#include "Engine/Core/Event/Events.hpp"


namespace Engine
{
    class CameraController
    {
        float aspectRatio;
        float zoomLevel;
        Camera camera;
        glm::vec3 position;


        bool OnMouseScroll(MouseScrollEvent& event);
        bool OnWindowResize(WindowResizeEvent& event);

        void UpdateCamera();


    public:
        CameraController(float aspectRatio);

        void OnUpdate(float dt);
        void OnEvent(Event& event);

        Camera& GetCamera() { return camera; }
    };
}
