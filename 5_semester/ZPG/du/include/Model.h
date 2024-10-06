#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

class Model {
public:
    GLuint VAO;
    GLuint VBO;
    GLsizei vertexCount;

    // Konstruktor přijímá pole vertexů a jeho velikost
    Model(float* vertices, size_t size);

    // Destruktor pro uvolnění zdrojů
    virtual ~Model();

    // Metoda pro vykreslení modelu
    virtual void draw();
};

#endif // MODEL_H