#pragma once
#include "Camera.hpp"
#include "../Event/Event.hpp"
#include "../Event/Events.hpp"


namespace Engine
{
    class CameraController
    {
        float aspectRatio;
        float zoomLevel;
        Camera camera;
        glm::vec3 position;


        void OnMouseScroll(Events::MouseScrollEvent& e);
        void OnWindowResize(Events::WindowResizeEvent& e);

        void UpdateCamera();


    public:
        CameraController(float aspectRatio);

        void OnUpdate(float dt);
        void OnEvent(Event& event);

        Camera& GetCamera() { return camera; }
    };
}
