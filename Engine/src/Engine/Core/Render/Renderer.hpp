#pragma once
#include "Engine/Engine.hpp"

namespace Engine
{
    class Renderer
    {
        UInt vao;
        UInt vbo;
        UInt idxVbo;

    public:
        Renderer() = default;

        void Setup();
        void NextBatch();
        void DrawQuad(glm::vec2 offset, glm::vec3 color, glm::vec2 scale = glm::vec3(1.0f, 1.0f, 0),
                      glm::vec3 rotation = {0, 0, 0}, float texture = 0);

        
        void DrawBatch();
    };
}
