#pragma once
#include "Engine/Core/Event/Event.hpp"

namespace Engine
{
    class Layer
    {
    public:
        Layer() = default;
        virtual ~Layer() = default;

        virtual void Init()
        {
        }

        virtual void Shutdown()
        {
        }

        virtual void OnEvent(Event& event)
        {
        }
        
        virtual void OnUpdate(float dt)
        {
        }

        virtual void OnRender()
        {
        }

        virtual void OnRenderImGui()
        {
        }
    };
}
