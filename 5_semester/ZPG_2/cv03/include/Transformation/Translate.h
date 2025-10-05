#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

class Translate : public Transform {
public:
    Translate();
    
    void translate(const glm::vec3& translation);
    const glm::mat4& getMatrix() const override;
    void reset() override;

private:
    glm::mat4 matrix;
};