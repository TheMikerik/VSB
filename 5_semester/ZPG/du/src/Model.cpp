#include "Model.h"

Model::Model(float* vertices, size_t size) {
    vertexCount = static_cast<GLsizei>(size / (3 * sizeof(float))); // 3 komponenty na vertex

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind a set of vertices (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // Vertex attribute pointer
    glEnableVertexAttribArray(0); // pozice v shaderu na location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Unbind VBO a VAO pro bezpečnost
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Model::~Model() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Model::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}