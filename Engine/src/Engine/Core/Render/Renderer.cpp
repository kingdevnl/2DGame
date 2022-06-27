#include "Renderer.hpp"
#include "Shader.hpp"

#include <gl/glew.h>
#include <glm/ext/matrix_transform.hpp>


namespace Engine
{
    struct Vertex
    {
        glm::vec3 coords;
        glm::vec3 color;
        glm::vec2 texCoords{0.0f, 0.0f};
        float textureID = 0;
    };


    std::vector<Vertex> vertices{};
    std::vector<unsigned int> indices{};

    void Renderer::Setup()
    {
        glGenVertexArrays(1, &vao);
    }

    void Renderer::NextBatch()
    {
        glBindVertexArray(vao);
        vertices.clear();
    }

    void Renderer::DrawQuad(glm::vec2 offset, glm::vec3 color, glm::vec2 scale, glm::vec3 rotation, float texture)
    {
        static const float size = 0.5f;


        static const float verts[] =
        {
            -size, size, 0, // top left
            -size, -size, 0, // bottom left
            size, -size, 0, // bottom right
            size, -size, 0, // bottom right
            size, size, 0, // top right
            -size, size, 0 // top left
        };

        static const float textCoords[] = {
            0, 1,
            0, 0,
            1, 0,
            1, 0,
            1, 1,
            0, 1
        };

        int tc = 0;
        for (int i = 0; i < sizeof(verts) / sizeof(float); i++)
        {
            Vertex vertex{};
            auto coords = glm::vec3(verts[i], verts[i + 1], verts[i + 2]);
            auto texCoord = glm::vec2(textCoords[tc], textCoords[tc + 1]);

            glm::mat4 transform = translate(glm::mat4(1.0), glm::vec3(offset.x, offset.y, 0));
            transform = rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
            transform = rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
            transform = rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));
            transform = glm::scale(transform, glm::vec3(scale.x, scale.y, 1));
            vertex.coords = transform * glm::vec4(coords, 1);
            vertex.color = color;
            vertex.texCoords = texCoord;

            vertex.textureID = texture == -1 ? 0 : texture + 1;


            i += 2;
            tc += 2;

            vertices.push_back(vertex);
        }
    }

    void Renderer::DrawBatch()
    {
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
        //
        // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
        // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) * 2));
        // glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        //                       (void*)(sizeof(glm::vec3) * 2 + sizeof(glm::vec2)));


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<const void*>(offsetof(Vertex, color)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<const void*>(offsetof(Vertex, texCoords)));
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              reinterpret_cast<const void*>(offsetof(Vertex, textureID)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);

        glBindVertexArray(0);
        glDeleteBuffers(1, &vbo);
    }
}
