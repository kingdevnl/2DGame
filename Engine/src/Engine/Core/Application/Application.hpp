#pragma once

#include "Layer.hpp"
#include "Engine/Core/Window/Window.hpp"
#include "Engine/Core/Event/Event.hpp"



int main(int argc, char** argv);

namespace Engine
{
    class Application
    {
    private:
        Ref<Window> window;
        std::vector<Layer*> layers{};
        static Application* instance;
        friend int ::main(int argc, char** argv);

    public:
        virtual ~Application() = default;
        Application(string name = "Application", int width = 1280, int height = 720);

        virtual void OnEvent(Event& event);


        void PushLayer(Layer* layer);
        

        Ref<Window> GetWindow()
        {
            return window;
        }

        static Application*  Get() { return instance; }

    private:
        void Run();
        void Shutdown();
    };

    Application* CreateApp();
}
