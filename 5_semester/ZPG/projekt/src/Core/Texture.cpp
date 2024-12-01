#include "Core/Texture.h"
#include "stb_image.h"
#include <iostream>

<<<<<<< HEAD

=======
>>>>>>> 783003c0f8698c5a6a0d2f713c85ebf89823a7c5
Texture::Texture(const std::string& path, bool gammaCorrection)
    : textureID(0), width(0), height(0), nrChannels(0), isCubemap(false)
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

<<<<<<< HEAD
        
=======
>>>>>>> 783003c0f8698c5a6a0d2f713c85ebf89823a7c5
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, 
                     (nrChannels == 1 ? GL_RED : (nrChannels == 3 ? GL_RGB : GL_RGBA)), 
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

<<<<<<< HEAD
        
=======
>>>>>>> 783003c0f8698c5a6a0d2f713c85ebf89823a7c5
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

<<<<<<< HEAD

=======
>>>>>>> 783003c0f8698c5a6a0d2f713c85ebf89823a7c5
Texture::Texture(const std::vector<std::string>& faces, bool gammaCorrection)
    : textureID(0), width(0), height(0), nrChannels(0), isCubemap(true)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
<<<<<<< HEAD
    stbi_set_flip_vertically_on_load(false); 
=======
    stbi_set_flip_vertically_on_load(false);
>>>>>>> 783003c0f8698c5a6a0d2f713c85ebf89823a7c5

    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = gammaCorrection ? GL_SRGB : GL_RGB;
            else if (nrChannels == 4)
                format = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
            else {
                std::cerr << "Unsupported number of channels: " << nrChannels << " in cubemap texture." << std::endl;
                stbi_image_free(data);
                continue;
            }

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, 
                         (nrChannels == 1 ? GL_RED : (nrChannels == 3 ? GL_RGB : GL_RGBA)),
                         GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
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
    if (isCubemap) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
}