#include "CompositeTransform.h"
#include <algorithm>

CompositeTransform::CompositeTransform() : cachedMatrix(1.0f), isDirty(true) {}

void CompositeTransform::addTransform(std::shared_ptr<Transform> transform) {
    transforms.push_back(transform);
    isDirty = true;
}

void CompositeTransform::removeTransform(std::shared_ptr<Transform> transform) {
    transforms.erase(
        std::remove(transforms.begin(), transforms.end(), transform),
        transforms.end()
    );
    isDirty = true;
}

const glm::mat4& CompositeTransform::getMatrix() const {
    if (isDirty) {
        updateMatrix();
    }
    return cachedMatrix;
}

void CompositeTransform::reset() {
    for (auto& transform : transforms) {
        transform->reset();
    }
    isDirty = true;
}

void CompositeTransform::updateMatrix() const {
    cachedMatrix = glm::mat4(1.0f);
    for (const auto& transform : transforms) {
        cachedMatrix = cachedMatrix * transform->getMatrix();
    }
    isDirty = false;
}