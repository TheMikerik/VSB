// CustomOperation.h
#pragma once
#include "Interfaces/ITransformationOperation.h"
#include <glm/glm.hpp>

class CustomOperation : public ITransformationOperation {
    glm::mat4 customMatrix;
public:
    CustomOperation() {
        customMatrix = glm::mat4(1.0f);
        customMatrix[3][3] = 20.0f;
    }
    
    void apply(glm::mat4& modelMatrix) const override {
        modelMatrix = modelMatrix * customMatrix;
    }
};