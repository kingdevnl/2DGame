#include "Shader.hpp"
#include "Engine/Core/Util/IO.hpp"

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
    bool Compile(UInt id, const char* msg)
    {
        GLint status;
        glCompileShader(id);
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE)
        {
            int INFO_LOG_LENGTH;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &INFO_LOG_LENGTH);
            auto infoLog = new char[INFO_LOG_LENGTH];
            glGetShaderInfoLog(id, INFO_LOG_LENGTH, nullptr, infoLog);
            ERROR("{} {} : {}", INFO_LOG_LENGTH, msg, infoLog);
            delete[] infoLog;
            glDeleteShader(id);
            return false;
        }
        return true;
    }

    int GetUniformLoc(int program, const char* name)
    {
        const int loc = glGetUniformLocation(program, name);
        if (loc == -1)
        {
            ERROR("Could not find uniform {}", name);
            return -1;
        }
        return loc;
    }

    Shader::Shader(string& vertex_source, string& fragment_source)
    {
        this->id = glCreateProgram();
        this->vertex = glCreateShader(GL_VERTEX_SHADER);
        this->fragment = glCreateShader(GL_FRAGMENT_SHADER);

        const char* vs = vertex_source.c_str();
        const char* fs = fragment_source.c_str();
        glShaderSource(this->vertex, 1, &vs, nullptr);
        glShaderSource(this->fragment, 1, &fs, nullptr);


        if (!Compile(this->vertex, "Failed to compile vertex shader"))
        {
            std::cin.get();
            exit(1);
        }

        if (!Compile(this->fragment, "Failed to compile fragment shader"))
        {
            std::cin.get();
            exit(1);
        }
        glAttachShader(this->id, this->vertex);
        glAttachShader(this->id, this->fragment);
        glLinkProgram(this->id);

        INFO("Created shader program {} {} {}", this->id, this->vertex, this->fragment);
    }


    void Shader::Bind() const
    {
        // set current shader program to this one

        currentShader = this;

        glUseProgram(this->id);
    }


    void Shader::Set(const char* name, glm::vec3 vector) const
    {
        glUniform3f(GetUniformLoc(this->id, name), vector.x, vector.y, vector.z);
    }

    void Shader::Set(const char* name, float value) const
    {
        glUniform1f(GetUniformLoc(this->id, name), value);
    }

    void Shader::Set(const char* name, glm::mat4 matrix) const
    {
        glUniformMatrix4fv(GetUniformLoc(this->id, name), 1, GL_FALSE, value_ptr(matrix));
    }

    void Shader::Set(const char* name, std::vector<float> vector) const
    {
        glUniform1fv(GetUniformLoc(this->id, name), vector.size(), vector.data());
    }

    void Shader::Set(const char* name, std::vector<int> vector) const
    {
        glUniform1iv(GetUniformLoc(this->id, name), vector.size(), vector.data());
    }


    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::Destroy() const
    {
        glDetachShader(this->id, this->vertex);
        glDetachShader(this->id, this->fragment);
        glDeleteShader(this->vertex);
        glDeleteShader(this->fragment);
        glDeleteProgram(this->id);
    }


    Ref<Shader> Shader::LoadFromFile(string vertexFile, string fragmentFile)
    {
        string vertex_source = IO::ReadFile(vertexFile.c_str());
        string fragment_source = IO::ReadFile(fragmentFile.c_str());

        
        
        return MakeRef<Shader>(vertex_source, fragment_source);
    }
}
