#pragma once

#include <glm/glm.hpp>
#include "Shaders/ShaderProgram.h"

class Material {
public:
    Material(const glm::vec3& ambient = glm::vec3(0.2f),
             const glm::vec3& diffuse = glm::vec3(0.5f),
             const glm::vec3& specular = glm::vec3(1.0f),
             float shininess = 32.0f);

    void apply(const ShaderProgram& shader) const;

    const glm::vec3& getAmbient() const;
    const glm::vec3& getDiffuse() const;
    const glm::vec3& getSpecular() const;
    float getShininess() const;

    void setAmbient(const glm::vec3& ambient);
    void setDiffuse(const glm::vec3& diffuse);
    void setSpecular(const glm::vec3& specular);
    void setShininess(float shininess);

private:
    glm::vec3 ambient;   
    glm::vec3 diffuse; 
    glm::vec3 specular;
    float shininess;
};