#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

class Model {
public:
    Model(float* vertices, size_t size);
    ~Model();

    void draw();

private:
    GLuint VAO, VBO;
    GLsizei vertexCount;
};

#endif // MODEL_H