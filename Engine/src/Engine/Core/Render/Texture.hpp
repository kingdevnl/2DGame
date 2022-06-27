#pragma once
#include "Engine/Engine.hpp"


namespace Engine::Texture
{
    UInt LoadTexture(const std::string& file);
    static UInt WHITE_TEXTURE;


    void CreateWhiteTexture();
}
