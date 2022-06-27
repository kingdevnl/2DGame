#include "Application.hpp"

#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


void uwu()
{
    bool show_demo_window = true;

    ImGui::ShowDemoWindow(&show_demo_window);
}

namespace Engine
{
    Application* Application::instance = nullptr;


    Application::Application(string name, int width, int height)
    {
        instance = this;
        window = MakeRef<Window>(width, height, name);
        window->Create();

    }

    

 

    void Application::OnEvent(Event& event)
    {
        for(const auto& layer : layers)
            layer->OnEvent(event);
    }

    void Application::PushLayer(Layer* layer)
    {
        layer->Init();
        this->layers.push_back(layer);
    }


    void Application::Shutdown()
    {
        spdlog::info("Shutting down...");
        for (const auto& layer : layers)
        {
            layer->Shutdown();
            delete layer;
        }
        layers.clear();
    }


    void Application::Run()
    {
        double time = 0;
        double delta = 0;
        double lastTime = 0;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
        ImGui_ImplOpenGL3_Init("#version 130");

        while (!glfwWindowShouldClose(window->GetHandle()))
        {
            window->Update();
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.181818f, 0.181818f, 0.181818f, 1);

        

          
            for (const auto& layer : layers)
            {
                layer->OnRender();
         
            }
            
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            for (const auto& layer : layers)
            {
                layer->OnRenderImGui();
            }
            
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            
            
            for (const auto& layer : layers)
            {
                layer->OnUpdate(static_cast<float>(delta));
            }
            
            
            glfwSwapBuffers(window->GetHandle());

            time = glfwGetTime();
            delta = time - lastTime;
            lastTime = time;
        }
        Shutdown();
        glfwTerminate();
    }
}
