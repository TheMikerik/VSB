// Transformation.h
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <glm/glm.hpp>

class Transformation {
public:
    Transformation();

    void translate(const glm::vec3& translation);
    void rotate(float angleDegrees, const glm::vec3& axis);
    void scale(const glm::vec3& scaleVec);

    const glm::mat4& getModelMatrix() const;

private:
    glm::mat4 modelMatrix;
};

#endif // TRANSFORMATION_H