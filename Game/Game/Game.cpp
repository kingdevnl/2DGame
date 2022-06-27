#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <Engine/Core/Application/Application.hpp>
#include <Engine/Core/Event/Events.hpp>
#include <Engine/Core/Render/Shader.hpp>


// ReSharper disable once CppUnusedIncludeDirective
#include <Engine/Core/Application/Boot.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Core/Camera/CameraController.hpp"
#include "Engine/Core/Render/Renderer.hpp"
#include "Engine/Core/Render/Texture.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

class GameLayer : public Engine::Layer
{
    Ref<Engine::Shader> shader;
    Engine::Renderer renderer{};
    UInt texture1 = -1;
    UInt texture2 = -1;
public:
    inline static Engine::CameraController cameraController = Engine::CameraController(1280.0f / 720.0f);

    GameLayer()
    {
    }

    void Init() override
    {
        spdlog::info("Layer Init");
        shader = Engine::Shader::LoadFromFile("Assets/shaders/basic.vert.glsl", "Assets/shaders/basic.frag.glsl");
        texture1 = Engine::Texture::LoadTexture("Assets/textures/test.png");
        texture2 = Engine::Texture::LoadTexture("Assets/textures/test2.png");
        renderer.Setup();
        glBindTextureUnit(0, Engine::Texture::WHITE_TEXTURE);
        glBindTextureUnit(1, texture1);
        glBindTextureUnit(2, texture2);
    }

    glm::vec3 rot{0, 0, 0};
	glm::vec3 pos{0, 0, 0};
	glm::vec3 color{0, 0, 1};
    void OnRender() override
    {
        
        shader->Bind();
        shader->Set("viewProjection", cameraController.GetCamera().GetViewProjectionMatrix());
        shader->Set("samplers", std::vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});


        renderer.NextBatch();

        glm::vec3 start(-0.5, -0.5, 0);

        for (int i = 0; i < 20; ++i)
        {
            for (int j = 0; j < 20; ++j)
            {
                glm::vec3 pos(i * 0.11f, j * 0.11f, 0);
                glm::vec3 color(0, 0, 0);
                

                renderer.DrawQuad(start + pos, color, {0.1, 0.1}, {0, 0, 0}, (i + j) % 2);
            }
        }

        renderer.DrawQuad({pos.x, pos.y}, color, {0.4, 0.4}, rot, -1);

        renderer.DrawBatch();

        shader->Unbind();
    }
	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}
	
    void OnRenderImGui() override
    {
        ImGui::Begin("test");
    	DrawVec3Control("Position", pos);
    	DrawVec3Control("Rotation", rot);
    	ImGui::ColorEdit3("Color", glm::value_ptr(color));


    	if(ImGui::Button("UWU"))
    	{
    		spdlog::info("UWU");
    	}
        ImGui::End();
    }

    
    void OnUpdate(float dt) override
    {
        cameraController.OnUpdate(dt);
    }

    void OnEvent(Engine::Event& event) override
    {
        cameraController.OnEvent(event);
    }

    void Shutdown() override
    {
        spdlog::info("GameLayer::Shutdown()");

        shader->Destroy();

        glDeleteTextures(1, &texture1);
        glDeleteTextures(1, &texture2);
    }
};


class HudLayer: public Engine::Layer
{
    void OnRenderImGui() override
    {
       auto camPos = GameLayer::cameraController.GetCamera().GetPosition();
        ImGui::Begin("Overlay");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::Text("Cam Pos: %.2f, %.2f, %.2f", camPos.x, camPos.y, camPos.z);
        ImGui::End();
    }
};


class Game : public Engine::Application
{
public:
    Game(): Application("Game")
    {
        spdlog::info("Game()");
        
        PushLayer(new GameLayer);
        PushLayer(new HudLayer);


    }

    bool OnKeyPressEvent(Engine::KeyPressEvent& e)
    {
        return true;
    }

    void OnEvent(Engine::Event& event) override
    {
        Application::OnEvent(event);
        Engine::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Engine::KeyPressEvent>(BIND_EVENT_FN(Game::OnKeyPressEvent));
    }
};


Engine::Application* Engine::CreateApp()
{
    return new Game();
}

