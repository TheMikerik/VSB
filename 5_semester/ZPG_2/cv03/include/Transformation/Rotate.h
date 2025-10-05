#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

class Rotate : public Transform {
public:
    Rotate();
    
    void rotate(float angleDegrees, const glm::vec3& axis);
    const glm::mat4& getMatrix() const override;
    void reset() override;

private:
    glm::mat4 matrix;
};