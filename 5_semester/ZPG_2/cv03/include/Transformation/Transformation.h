// include/Transformation/Transformation.h
#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "Transform.h"
#include "CompositeTransform.h"

class Transformation {
public:
    Transformation();
    
    void translate(const glm::vec3& translation);
    void rotate(float angleDegrees, const glm::vec3& axis);
    void scale(const glm::vec3& scaleVec);
    void updateDynamicRotation(float deltaTime);
    
    const glm::mat4& getModelMatrix() const;
    void reset();

private:
    std::shared_ptr<CompositeTransform> compositeTransform;
    std::shared_ptr<Translate> translateTransform;
    std::shared_ptr<Rotate> rotateTransform;
    std::shared_ptr<Scale> scaleTransform;
    std::shared_ptr<DynamicRotation> dynamicRotationTransform;
};