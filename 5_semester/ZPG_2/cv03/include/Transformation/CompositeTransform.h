#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "Transform.h"

class CompositeTransform : public Transform {
public:
    CompositeTransform();
    
    void addTransform(std::shared_ptr<Transform> transform);
    void removeTransform(std::shared_ptr<Transform> transform);
    
    const glm::mat4& getMatrix() const override;
    void reset() override;

private:
    std::vector<std::shared_ptr<Transform>> transforms;
    mutable glm::mat4 cachedMatrix;
    mutable bool isDirty;
    
    void updateMatrix() const;
};