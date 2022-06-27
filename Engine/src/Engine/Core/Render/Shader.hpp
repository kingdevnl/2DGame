#pragma once
#include "Engine/Engine.hpp"


namespace Engine
{
    class Shader
    {
    public:
        unsigned int id, vertex, fragment;

        Shader(string& vertex_source, string& fragment_source);


        void Bind() const;
        void Set(const char* name, glm::vec3 vector) const;
        void Set(const char* name, float value) const;
        void Set(const char* name, glm::mat4 matrix) const;
        void Set(const char* name, std::vector<float> vector) const;
        void Set(const char* name, std::vector<int> vector) const;


        void Unbind() const;
        void Destroy() const;

        static Ref<Shader> LoadFromFile(string vertexFile, string fragmentFile);
        inline static const Shader* currentShader = nullptr;
    };
}
