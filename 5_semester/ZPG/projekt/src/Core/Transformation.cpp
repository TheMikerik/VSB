#include "Core/Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation()
    : modelMatrix(glm::mat4(1.0f))
{}

void Transformation::addOperation(const std::shared_ptr<ITransformationOperation>& operation) {
    operations.push_back(operation);
}

const glm::mat4& Transformation::getModelMatrix() const {
    glm::mat4 tempModelMatrix = glm::mat4(1.0f);
    for (const auto& op : operations) {
        op->apply(tempModelMatrix);
    }
    return tempModelMatrix;
}