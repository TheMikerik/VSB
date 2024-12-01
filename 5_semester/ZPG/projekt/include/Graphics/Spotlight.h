#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "Shaders/ShaderProgram.h"

class Spotlight {
public:
    Spotlight(const glm::vec3& position, const glm::vec3& direction);
    void update(const glm::vec3& position, const glm::vec3& direction);
    void applyToShader(const std::shared_ptr<ShaderProgram>& shader);

    glm::vec3 getPosition() const { return position; }
    glm::vec3 getDirection() const { return direction; }

private:
    glm::vec3 position;
    glm::vec3 direction;
};