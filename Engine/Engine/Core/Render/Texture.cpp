#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../Vendor/stb_image.h"
#include <gl/glew.h>


namespace Engine
{
    UInt Texture::LoadTexture(const std::string& file)
    {
        if (!std::filesystem::exists(file))
        {
            ERROR("Texture file {} does not exist", file);
            return -1;
        }

        int w, h, bits;
        stbi_set_flip_vertically_on_load(1);
        auto* pixels = stbi_load(file.c_str(), &w, &h, &bits, STBI_rgb);
        GLuint textureID;
        glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        stbi_image_free(pixels);
        glBindTexture(GL_TEXTURE_2D, 0);
        INFO("Loaded texture {}", file);
        return textureID;
    }

    void Texture::CreateWhiteTexture()
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &WHITE_TEXTURE);
        glBindTexture(GL_TEXTURE_2D, WHITE_TEXTURE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        uint32_t color = 0xFFFFFFFF;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
