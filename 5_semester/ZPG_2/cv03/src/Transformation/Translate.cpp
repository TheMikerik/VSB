#include "Translate.h"
#include <glm/gtc/matrix_transform.hpp>

Translate::Translate() : matrix(1.0f) {}

void Translate::translate(const glm::vec3& translation) {
    matrix = glm::translate(matrix, translation);
}

const glm::mat4& Translate::getMatrix() const {
    return matrix;
}

void Translate::reset() {
    matrix = glm::mat4(1.0f);
}