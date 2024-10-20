// DrawableObject.cpp
#include "DrawableObject.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

DrawableObject::DrawableObject(std::shared_ptr<Model> model,
                               std::shared_ptr<ShaderProgram> shaderProgram,
                               const Transformation& transformation)
    : model(model), shaderProgram(shaderProgram), transformation(transformation)
{}

void DrawableObject::render() const
{
    shaderProgram->use();

    // Set the model matrix uniform
    GLint modelLoc = glGetUniformLocation(shaderProgram->getProgramID(), "modelMatrix");
    if (modelLoc == -1) {
        std::cerr << "Could not find uniform 'modelMatrix' in shader program." << std::endl;
    } else {
        glm::mat4 modelMat = transformation.getModelMatrix();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    }

    model->bind();
    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
    model->unbind();
}

void DrawableObject::setTransformation(const Transformation& trans)
{
    transformation = trans;
}

Transformation& DrawableObject::getTransformation()
{
    return transformation;
}