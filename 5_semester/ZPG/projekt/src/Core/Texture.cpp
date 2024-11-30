// src/Core/Texture.cpp
#include "Core/Texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string& path, bool gammaCorrection)
    : textureID(0), width(0), height(0), nrChannels(0)
{
    stbi_set_flip_vertically_on_load(true);
    
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = gammaCorrection ? GL_SRGB : GL_RGB;
        else if (nrChannels == 4)
            format = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
        else {
            std::cerr << "Unsupported number of channels: " << nrChannels << std::endl;
            stbi_image_free(data);
            return;
        }

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Load texture data into OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, 
                     nrChannels == 1 ? GL_RED : (nrChannels == 3 ? GL_RGB : GL_RGBA), 
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Set texture wrapping/filtering options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }
    else {
        std::cerr << "Failed to load texture at path: " << path << std::endl;
        stbi_image_free(data);
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}

void Texture::bind(GLuint unit) const
{
    if (unit > 31) {
        std::cerr << "Texture unit " << unit << " is not supported. Max is 31." << std::endl;
        return;
    }
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}