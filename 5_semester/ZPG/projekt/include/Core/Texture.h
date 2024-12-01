#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>

class Texture {
public:
    Texture(const std::string& path, bool gammaCorrection = false);
    Texture(const std::vector<std::string>& faces, bool gammaCorrection = false);

    ~Texture();

    void bind(GLuint unit) const;

    GLuint getID() const { return textureID; }

private:
    GLuint textureID;
    int width, height, nrChannels;
    bool isCubemap;
};