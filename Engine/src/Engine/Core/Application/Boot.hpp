#pragma once
#include "Application.hpp"
#include "Engine/Core/Render/Texture.hpp"


extern Engine::Application* Engine::CreateApp();


int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::trace);
    
    auto app = Engine::CreateApp();
    Engine::Texture::CreateWhiteTexture();
    app->Run();

    glDeleteTextures(1, &Engine::Texture::WHITE_TEXTURE);

    delete app;
}