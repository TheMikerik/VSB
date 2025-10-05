#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation() : modelMatrix(1.0f) {}

void Transformation::translate(const glm::vec3& translation) {
    translateTransform.translate(translation);
    updateModelMatrix();
}

void Transformation::rotate(float angleDegrees, const glm::vec3& axis) {
    rotateTransform.rotate(angleDegrees, axis);
    updateModelMatrix();
}

void Transformation::scale(const glm::vec3& scaleVec) {
    scaleTransform.scale(scaleVec);
    updateModelMatrix();
}

void Transformation::updateDynamicRotation(float deltaTime) {
    dynamicRotationTransform.update(deltaTime);
    updateModelMatrix();
}

const glm::mat4& Transformation::getModelMatrix() const {
    return modelMatrix;
}

void Transformation::reset() {
    translateTransform.reset();
    rotateTransform.reset();
    scaleTransform.reset();
    dynamicRotationTransform.reset();
    modelMatrix = glm::mat4(1.0f);
}

void Transformation::updateModelMatrix() {
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = modelMatrix * translateTransform.getMatrix();
    modelMatrix = modelMatrix * rotateTransform.getMatrix();
    modelMatrix = modelMatrix * dynamicRotationTransform.getMatrix();
    modelMatrix = modelMatrix * scaleTransform.getMatrix();
}