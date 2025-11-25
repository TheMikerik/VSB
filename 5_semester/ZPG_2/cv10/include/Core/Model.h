#pragma once

#include <vector>
#include <GL/glew.h>

class Model {
public:
    Model(const std::vector<float>& vertices, bool hasTexCoords = false);
    Model(const char* name);
    ~Model();

    void bind() const;
    void unbind() const;
    GLsizei getVertexCount() const { return vertexCount; }

private:
    GLuint VAO;
    GLuint VBO;
    GLsizei vertexCount;
};