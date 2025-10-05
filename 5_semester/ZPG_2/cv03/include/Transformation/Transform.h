#pragma once
#include <glm/glm.hpp>

class Transform {
public:
    virtual ~Transform() = default;
    virtual const glm::mat4& getMatrix() const = 0;
    virtual void reset() = 0;
};