// Transformation.cpp
#include "Core/Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation()
    : modelMatrix(1.0f)
{}

void Transformation::translate(const glm::vec3& translation){
    modelMatrix = glm::translate(modelMatrix, translation);
}

void Transformation::rotate(float angleDegrees, const glm::vec3& axis){
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angleDegrees), axis);
}

void Transformation::scale(const glm::vec3& scaleVec){
    modelMatrix = glm::scale(modelMatrix, scaleVec);
}

const glm::mat4& Transformation::getModelMatrix() const{
    return modelMatrix;
}