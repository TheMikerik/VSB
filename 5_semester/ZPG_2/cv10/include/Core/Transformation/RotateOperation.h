// RotateOperation.h
#include "Interfaces/ITransformationOperation.h"

class RotateOperation : public ITransformationOperation {
    float angleDegrees;
    glm::vec3 axis;
public:
    RotateOperation(float angleDegrees, const glm::vec3& axis) : angleDegrees(angleDegrees), axis(axis) {}
    void apply(glm::mat4& modelMatrix) const override {
        modelMatrix = glm::rotate(modelMatrix, glm::radians(angleDegrees), axis);
    }
};