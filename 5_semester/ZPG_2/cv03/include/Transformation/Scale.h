#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

class Scale : public Transform {
public:
    Scale();
    
    void scale(const glm::vec3& scaleVec);
    const glm::mat4& getMatrix() const override;
    void reset() override;

private:
    glm::mat4 matrix;
};