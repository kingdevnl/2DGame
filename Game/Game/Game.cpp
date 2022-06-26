#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

#include <Engine/Core/App.hpp>
#include <Engine/Core/Event/Events.hpp>
#include <Engine/Core/Camera/Camera.hpp>
#include <Engine/Core/Render/Renderer.hpp>
#include <Engine/Core/Render/Shader.hpp>
#include <Engine/Core/Render/Texture.hpp>
#include <Engine/Core/Camera/CameraController.hpp>


float pos[2] = {-0.5, -0.5};

class Game : public Engine::Application
{
public:
    Engine::CameraController cameraController;
    Ref<Engine::Shader> shader;
    Ref<Engine::Shader> basicShader;
    Engine::Renderer renderer;
    GLuint texture1, texture2;

    //Engine::Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    Game()
        : Application("Game", 1280, 720),
          cameraController(Engine::CameraController(1280.0f / 720.0f)),
          renderer(Engine::Renderer{})
    {
    }

    void Init() override
    {
        INFO("[Game] Game Init");
        shader = Engine::Shader::LoadFromFile("Assets/shaders/game.vert.glsl", "Assets/shaders/game.frag.glsl");
        basicShader = Engine::Shader::LoadFromFile("Assets/shaders/basic.vert.glsl", "Assets/shaders/basic.frag.glsl");


        texture1 = Engine::Texture::LoadTexture("Assets/textures/test.png");
        texture2 = Engine::Texture::LoadTexture("Assets/textures/test2.png");


        glBindTextureUnit(0, Engine::Texture::WHITE_TEXTURE);
        glBindTextureUnit(1, texture1);
        glBindTextureUnit(2, texture2);
    }


    void OnRender() override
    {
        basicShader->Bind();
        basicShader->Set("viewProjection", cameraController.GetCamera().GetViewProjectionMatrix());
        basicShader->Set("samplers", std::vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});


        renderer.NextBatch();


        glm::vec3 start(-0.5, -0.5, 0);

        for (int i = 0; i < 20; ++i)
        {
            for (int j = 0; j < 20; ++j)
            {
                glm::vec3 pos(i * 0.11f, j * 0.11f, 0);
                glm::vec3 color(0, 0, 0);
                renderer.DrawQuad(start + pos, color, glm::vec3(0.1, 0.1, 0), 0, (i + j) % 2);
            }
        }

        renderer.DrawQuad({pos[0], pos[1]}, {0, 1, 0}, {0.2, 0.2, 0}, 0, -1);
        renderer.DrawBatch();

        basicShader->Unbind();
    }


    void OnRenderImGui() override
    {
        ImGui::Begin("Overlay");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        auto const camPos = cameraController.GetCamera().GetPosition();
        ImGui::Text("Cam Pos: %.2f, %.2f, %.2f", camPos.x, camPos.y, camPos.z);
        ImGui::Text("Cam Rot: %.2f", cameraController.GetCamera().GetRotation());
        //slider that has a increment of 0.1f
        ImGui::SliderFloat2("Pos", pos, -2.5, 2.5);
        ImGui::End();

    }

    void OnUpdate(float dt) override
    {
        if (ImGui::IsAnyItemActive()) return;
        cameraController.OnUpdate(dt);
    }

    void Shutdown() override
    {
        INFO("[Game] Game Shutdown");

        shader->Destroy();
        basicShader->Destroy();

        glDeleteTextures(1, &texture1);
        glDeleteTextures(1, &texture2);
    }


    void OnEvent(Engine::Event& event) override
    {

        spdlog::info(ImGui::IsAnyItemActive());
        if (ImGui::IsAnyItemActive()) return;
        
        if (event.type == Engine::EventType::KEY_EVENT)
        {
            auto keyEvent = static_cast<Engine::Events::KeyEvent&>(event);

            if (keyEvent.action == GLFW_PRESS)
            {
                if (keyEvent.key == GLFW_KEY_ESCAPE)
                {
                    glfwSetWindowShouldClose(window->GetHandle(), 1);
                }
            }
        }



        cameraController.OnEvent(event);
    }
};


int main(int argc, char* argv[])
{
    Engine::Application::Boot(MakeRef<Game>());
}
