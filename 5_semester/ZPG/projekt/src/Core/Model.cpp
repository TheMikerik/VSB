#include "Core/Model.h"
#include <cstdlib>
#include <iostream>

Model::Model(const std::vector<float>& vertices, bool hasTexCoords)
    : VAO(0), VBO(0), vertexCount(0), hasTexCoords(hasTexCoords)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (hasTexCoords ? 8 : 6) * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (hasTexCoords ? 8 : 6) * sizeof(float), (void*)(3 * sizeof(float)));

    if (hasTexCoords) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    vertexCount = hasTexCoords ? static_cast<GLsizei>(vertices.size() / 8)
                               : static_cast<GLsizei>(vertices.size() / 6);
}

Model::~Model()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Model::bind() const
{
    glBindVertexArray(VAO);
}

void Model::unbind() const
{
    glBindVertexArray(0);
}