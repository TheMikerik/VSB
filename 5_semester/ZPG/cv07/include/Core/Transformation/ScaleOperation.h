// ScaleOperation.h
#include "Interfaces/ITransformationOperation.h"

class ScaleOperation : public ITransformationOperation {
    glm::vec3 scaleVec;
public:
    ScaleOperation(const glm::vec3& scaleVec) : scaleVec(scaleVec) {}
    void apply(glm::mat4& modelMatrix) const override {
        modelMatrix = glm::scale(modelMatrix, scaleVec);
    }
};