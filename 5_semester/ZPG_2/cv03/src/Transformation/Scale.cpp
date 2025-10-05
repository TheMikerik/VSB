#include "Scale.h"
#include <glm/gtc/matrix_transform.hpp>

Scale::Scale() : matrix(1.0f) {}

void Scale::scale(const glm::vec3& scaleVec) {
    matrix = glm::scale(matrix, scaleVec);
}

const glm::mat4& Scale::getMatrix() const {
    return matrix;
}

void Scale::reset() {
    matrix = glm::mat4(1.0f);
}