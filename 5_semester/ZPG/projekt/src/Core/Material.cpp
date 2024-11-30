// Material.cpp
#include "Core/Material.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Material::Material(const glm::vec3& ambient,
                   const glm::vec3& diffuse,
                   const glm::vec3& specular,
                   float shininess)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

void Material::apply(const ShaderProgram& shader) const {
    shader.use();

    GLint ambientLoc = glGetUniformLocation(shader.getProgramID(), "materialAmbient");
    GLint diffuseLoc = glGetUniformLocation(shader.getProgramID(), "materialDiffuse");
    GLint specularLoc = glGetUniformLocation(shader.getProgramID(), "materialSpecular");
    GLint shininessLoc = glGetUniformLocation(shader.getProgramID(), "materialShininess");

    glUniform3fv(ambientLoc, 1, glm::value_ptr(ambient));
    glUniform3fv(diffuseLoc, 1, glm::value_ptr(diffuse));
    glUniform3fv(specularLoc, 1, glm::value_ptr(specular));
    glUniform1f(shininessLoc, shininess);
}

// Getters
const glm::vec3& Material::getAmbient() const { return ambient; }
const glm::vec3& Material::getDiffuse() const { return diffuse; }
const glm::vec3& Material::getSpecular() const { return specular; }
float Material::getShininess() const { return shininess; }

// Setters
void Material::setAmbient(const glm::vec3& ambient) { this->ambient = ambient; }
void Material::setDiffuse(const glm::vec3& diffuse) { this->diffuse = diffuse; }
void Material::setSpecular(const glm::vec3& specular) { this->specular = specular; }
void Material::setShininess(float shininess) { this->shininess = shininess; }