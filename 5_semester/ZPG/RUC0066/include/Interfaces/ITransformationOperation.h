#pragma once

#include <glm/glm.hpp>

class ITransformationOperation {
public:
    virtual ~ITransformationOperation() = default;
    virtual void apply(glm::mat4& modelMatrix) const = 0;
};