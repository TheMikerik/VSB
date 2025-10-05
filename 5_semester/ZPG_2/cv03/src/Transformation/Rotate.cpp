#include "Rotate.h"
#include <glm/gtc/matrix_transform.hpp>

Rotate::Rotate() : matrix(1.0f) {}

void Rotate::rotate(float angleDegrees, const glm::vec3& axis) {
    matrix = glm::rotate(matrix, glm::radians(angleDegrees), axis);
}

const glm::mat4& Rotate::getMatrix() const {
    return matrix;
}

void Rotate::reset() {
    matrix = glm::mat4(1.0f);
}