// DrawableObject.cpp
#include "Graphics/DrawableObject.h"
#include "Core/Transformation.h"
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

    glUseProgram(0);
}


//TODO: Drawable object by mel mit pouze set a get transf!! Editnout
void DrawableObject::setShader(std::shared_ptr<ShaderProgram> shd) {
    shaderProgram = shd;
}

void DrawableObject::setTransformation(const Transformation& trans)
{
    transformation = trans;
}

Transformation& DrawableObject::getTransformation()
{
    return transformation;
}

glm::vec3 DrawableObject::getPosition() const {
    glm::mat4 modelMatrix = transformation.getModelMatrix();
    return glm::vec3(modelMatrix[3]);
}