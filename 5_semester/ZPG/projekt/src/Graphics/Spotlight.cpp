// Spotlight.cpp
#include "Graphics/Spotlight.h"
#include <glm/gtc/type_ptr.hpp>

Spotlight::Spotlight(const glm::vec3& position, const glm::vec3& direction)
    : position(position), direction(direction) {}

void Spotlight::update(const glm::vec3& position, const glm::vec3& direction) {
    this->position = position;
    this->direction = direction;
}

void Spotlight::applyToShader(const std::shared_ptr<ShaderProgram>& shader) {
    shader->use();

    GLint spotDirLoc = glGetUniformLocation(shader->getProgramID(), "spotDir");
    if (spotDirLoc != -1) {
        glUniform3fv(spotDirLoc, 1, glm::value_ptr(direction));
    }
    GLint lightPosLoc = glGetUniformLocation(shader->getProgramID(), "lightPos");
    if (lightPosLoc != -1) {
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(position));
    }
}