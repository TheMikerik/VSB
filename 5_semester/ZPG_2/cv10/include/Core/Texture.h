#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>

class Texture {
public:
    Texture(const std::string& path);
    Texture(const std::vector<std::string>& faces);

    ~Texture();

    void bind(GLuint unit) const;

    GLuint getID() const { return textureID; }

private:
    GLuint textureID;
    int width, height;
    bool isCubemap;
};