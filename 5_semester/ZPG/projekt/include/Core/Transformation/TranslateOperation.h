// TranslateOperation.h
#include "Interfaces/ITransformationOperation.h"

class TranslateOperation : public ITransformationOperation {
    glm::vec3 translation;
public:
    TranslateOperation(const glm::vec3& translation) : translation(translation) {}
    void apply(glm::mat4& modelMatrix) const override {
        modelMatrix = glm::translate(modelMatrix, translation);
    }
};