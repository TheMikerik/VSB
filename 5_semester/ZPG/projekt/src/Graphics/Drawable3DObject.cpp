#include "Graphics/Drawable3DObject.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Drawable3DObject::Drawable3DObject(std::shared_ptr<Object> model,
                                   std::shared_ptr<ShaderProgram> shaderProgram,
                                   const Transformation& transformation,
                                   const Material& material,
                                   std::shared_ptr<Texture> texture)
    : model(model), 
      shaderProgram(shaderProgram),
      transformation(transformation), 
      material(material), 
      texture(texture)
{}

Drawable3DObject::Drawable3DObject(std::shared_ptr<Object> model,
                                   std::shared_ptr<ShaderProgram> shaderProgram,
                                   const Transformation& transformation,
                                   std::shared_ptr<Texture> texture)
    : model(model), 
      shaderProgram(shaderProgram),
      transformation(transformation), 
      texture(texture)
{}

void Drawable3DObject::render(const glm::mat4& view, const glm::mat4& projection) const {
    if (!shaderProgram || !model) {
        std::cerr << "ShaderProgram or Object is not set for Drawable3DObject." << std::endl;
        return;
    }

    shaderProgram->use();

    
    glm::mat4 modelMatrix = transformation.getModelMatrix();
    shaderProgram->setMat4("viewMatrix", view);
    shaderProgram->setMat4("projectionMatrix", projection);
    shaderProgram->setMat4("modelMatrix", modelMatrix);

    material.apply(*shaderProgram);

    
    if (texture) {
        shaderProgram->setBool("hasTexture", true);
        texture->bind(0); 

        shaderProgram->setInt("texture_diffuse1", 0);
    } else {
        shaderProgram->setBool("hasTexture", false);
    }

    
    model->render(shaderProgram, view, projection, modelMatrix);

    glUseProgram(0);
}



void Drawable3DObject::setShader(std::shared_ptr<ShaderProgram> shd) {
    shaderProgram = shd;
}

void Drawable3DObject::setTransformation(const Transformation& trans) {
    transformation = trans;
}

Transformation& Drawable3DObject::getTransformation() {
    return transformation;
}

void Drawable3DObject::setMaterial(const Material& mat) {
    material = mat;
}

const Material& Drawable3DObject::getMaterial() const {
    return material;
}

void Drawable3DObject::setTexture(std::shared_ptr<Texture> tex) {
    texture = tex;
}

std::shared_ptr<Texture> Drawable3DObject::getTexture() const {
    return texture;
}