#include "DynamicRotation.h"
#include <glm/gtc/matrix_transform.hpp>

DynamicRotation::DynamicRotation() 
    : matrix(1.0f), axis(0.0f, 1.0f, 0.0f), rotationSpeed(90.0f), currentAngle(0.0f) {}

void DynamicRotation::update(float deltaTime) {
    currentAngle += rotationSpeed * deltaTime;
    matrix = glm::rotate(glm::mat4(1.0f), glm::radians(currentAngle), axis);
}

void DynamicRotation::setRotationSpeed(float speed) {
    rotationSpeed = speed;
}

void DynamicRotation::setAxis(const glm::vec3& newAxis) {
    axis = glm::normalize(newAxis);
}

const glm::mat4& DynamicRotation::getMatrix() const {
    return matrix;
}

void DynamicRotation::reset() {
    matrix = glm::mat4(1.0f);
    currentAngle = 0.0f;
}