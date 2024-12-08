#pragma once

#include <vector>
#include <GL/glew.h>

class SkyboxModel {
public:
    SkyboxModel(const std::vector<float>& vertices);
    ~SkyboxModel();

    void bind() const;
    void unbind() const;
    GLsizei getVertexCount() const { return vertexCount; }

private:
    GLuint VAO;
    GLuint VBO;
    GLsizei vertexCount;
};