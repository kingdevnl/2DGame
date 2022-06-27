#pragma once

#include "Core/Event/Event.hpp"
#include "Core/Window/Window.hpp"
#include "Engine.hpp"

namespace Engine
{
    class Application
    {
    public:
        virtual ~Application() = default;
        const string name;
        Ref<Window> window;
        Application(string name, int width, int height);

        virtual void Init() = 0;
        virtual void Shutdown() = 0;

        virtual void OnUpdate(float dt)
        {
        }

        virtual void OnRender()
        {
        }

        virtual void OnRenderImGui()
        {
        }

        virtual void OnEvent(Event& event)
        {
        }

        static void Boot(Ref<Application> app);
        inline static Ref<Application> app = nullptr;
    };
}
