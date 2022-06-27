#pragma once
#include "Engine/Engine.hpp"


namespace Engine::IO
{
    static std::string ReadFile(const char* fileName)
    {
        std::string content;
        std::ifstream fileStream(fileName, std::ios::in);

        if (!fileStream.is_open())
        {
            CRITICAL("Could not read file {}. File does not exist.", fileName);
            exit(1);
            return "";
        }

        std::string line = "";
        while (!fileStream.eof())
        {
            std::getline(fileStream, line);
            content.append(line + "\n");
        }

        fileStream.close();
        return content;
    }
}
