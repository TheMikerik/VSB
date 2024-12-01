#include "Graphics/DrawableObject.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

DrawableObject::DrawableObject(std::shared_ptr<Model> model,
                               std::shared_ptr<ShaderProgram> shaderProgram,
                               const Transformation& transformation,
                               const Material& material,
                               std::shared_ptr<Texture> texture)
    : model(model), shaderProgram(shaderProgram),
      transformation(transformation), material(material), texture(texture)
{}

void DrawableObject::render() const {
    shaderProgram->use();

    
    GLint modelLoc = glGetUniformLocation(shaderProgram->getProgramID(), "modelMatrix");
    if (modelLoc == -1) {
        std::cerr << "Could not find uniform 'modelMatrix' in shader program." << std::endl;
    } else {
        glm::mat4 modelMat = transformation.getModelMatrix();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    }

    material.apply(*shaderProgram);

    if (texture) {
        shaderProgram->setBool("hasTexture", true);
        texture->bind(0); 
        GLint texLoc = glGetUniformLocation(shaderProgram->getProgramID(), "texture_diffuse1");
        if (texLoc != -1) {
            glUniform1i(texLoc, 0); 
        }
    } else {
        shaderProgram->setBool("hasTexture", false);
    }

    model->bind();
    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
    model->unbind();

    glUseProgram(0);
}

void DrawableObject::setShader(std::shared_ptr<ShaderProgram> shd) {
    shaderProgram = shd;
}

void DrawableObject::setTransformation(const Transformation& trans) {
    transformation = trans;
}

Transformation& DrawableObject::getTransformation() {
    return transformation;
}

void DrawableObject::setMaterial(const Material& mat) {
    material = mat;
}

const Material& DrawableObject::getMaterial() const {
    return material;
}

void DrawableObject::setTexture(std::shared_ptr<Texture> tex) {
    texture = tex;
}

std::shared_ptr<Texture> DrawableObject::getTexture() const {
    return texture;
}

glm::vec3 DrawableObject::getPosition() const {
    glm::mat4 modelMatrix = transformation.getModelMatrix();
    return glm::vec3(modelMatrix[3]);
}