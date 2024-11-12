#pragma once

#include <memory>
#include <vector>
#include <glm/mat4x4.hpp>
#include "Interfaces/ITransformationOperation.h"

class Transformation {
private:
    std::vector<std::shared_ptr<ITransformationOperation>> operations;
    glm::mat4 modelMatrix;

public:
    Transformation();
    void addOperation(const std::shared_ptr<ITransformationOperation>& operation);
    void clearOperations();
    const glm::mat4& getModelMatrix() const;
};