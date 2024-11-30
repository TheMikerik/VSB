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

    if (ambientLoc != -1) {
        glUniform3fv(ambientLoc, 1, glm::value_ptr(ambient));
    } else {
        std::cerr << "Warning: 'materialAmbient' uniform not found in shader." << std::endl;
    }

    if (diffuseLoc != -1) {
        glUniform3fv(diffuseLoc, 1, glm::value_ptr(diffuse));
    } else {
        std::cerr << "Warning: 'materialDiffuse' uniform not found in shader." << std::endl;
    }

    if (specularLoc != -1) {
        glUniform3fv(specularLoc, 1, glm::value_ptr(specular));
    } else {
        std::cerr << "Warning: 'materialSpecular' uniform not found in shader." << std::endl;
    }

    if (shininessLoc != -1) {
        glUniform1f(shininessLoc, shininess);
    } else {
        std::cerr << "Warning: 'materialShininess' uniform not found in shader." << std::endl;
    }

    // Optionally, unbind the shader if necessary
    // glUseProgram(0);
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