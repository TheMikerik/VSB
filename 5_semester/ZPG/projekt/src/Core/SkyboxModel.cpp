// Core/SkyboxModel.cpp
#include "Core/SkyboxModel.h"
#include <iostream>

SkyboxModel::SkyboxModel(const std::vector<float>& vertices)
    : VAO(0), VBO(0), vertexCount(0)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    vertexCount = static_cast<GLsizei>(vertices.size() / 3);
}

SkyboxModel::~SkyboxModel()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void SkyboxModel::bind() const
{
    glBindVertexArray(VAO);
}

void SkyboxModel::unbind() const
{
    glBindVertexArray(0);
}