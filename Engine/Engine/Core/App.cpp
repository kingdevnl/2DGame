#include "App.hpp"

#include <gl/glew.h>

#include "Window/Window.hpp"
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Render/Texture.hpp"

namespace Engine
{
    Application::Application(string name, int width, int height)
        : name(name)
    {
        this->window = MakeRef<Window>(width, height, name);
    }

    void Application::Boot(Ref<Application> app)
    {
        spdlog::set_level(spdlog::level::trace);
        Application::app = app;

        INFO("[Engine] Booting up application {}", app->name);

        const auto window = app->window;
        window->Create();

        Texture::CreateWhiteTexture();


        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window->GetHandle(), true);
        ImGui_ImplOpenGL3_Init("#version 130");

        app->Init();


        double time = 0;
        double delta = 0;
        double lastTime = 0;

        while (!glfwWindowShouldClose(window->GetHandle()))
        {
            window->Update();

            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.181818f, 0.181818f, 0.181818f, 1);

            app->OnRender();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            app->OnRenderImGui();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window->GetHandle());

            time = glfwGetTime();
            delta = time - lastTime;
            lastTime = time;
            app->OnUpdate(static_cast<float>(delta));
        }
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        window->Destroy();
        app->Shutdown();
    }
}
