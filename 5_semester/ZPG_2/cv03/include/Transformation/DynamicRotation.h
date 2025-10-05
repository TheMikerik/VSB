#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

class DynamicRotation : public Transform {
public:
    DynamicRotation();
    
    void update(float deltaTime);
    void setRotationSpeed(float speed);
    void setAxis(const glm::vec3& axis);
    const glm::mat4& getMatrix() const override;
    void reset() override;

private:
    glm::mat4 matrix;
    glm::vec3 axis;
    float rotationSpeed;
    float currentAngle;
};