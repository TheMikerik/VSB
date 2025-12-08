// DrawableObject.cpp
#include "Graphics/DrawableObject.h"
#include "Core/Transformation.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

DrawableObject::DrawableObject(std::shared_ptr<Model> model,
                                std::shared_ptr<ShaderProgram> shaderProgram,
                                const Transformation& transformation)
    : model(model), shaderProgram(shaderProgram), transformation(transformation),
      objectID(0), selected(false)
{}

void DrawableObject::render() const
{
    shaderProgram->use();

    GLint selectedLoc = glGetUniformLocation(shaderProgram->getProgramID(), "isSelected");
    if (selectedLoc != -1) {
        glUniform1i(selectedLoc, selected ? 1 : 0);
    }

    GLint useTextureLoc = glGetUniformLocation(shaderProgram->getProgramID(), "hasTexture");
    if (useTextureLoc != -1) {
        glUniform1i(useTextureLoc, textures.empty() ? 0 : 1);
    }

    for (const auto& binding : textures) {
        binding.texture->bind(binding.unit);
        GLint samplerLoc = glGetUniformLocation(shaderProgram->getProgramID(), binding.uniformName.c_str());
        if (samplerLoc != -1) {
            glUniform1i(samplerLoc, binding.unit);
        }
    }

    GLint modelLoc = glGetUniformLocation(shaderProgram->getProgramID(), "modelMatrix");
    if (modelLoc != -1) {
        glm::mat4 modelMat = transformation.getModelMatrix();
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    }

    model->bind();
    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
    model->unbind();

    glUseProgram(0);
}

void DrawableObject::setID(GLuint id) {
    objectID = id;
}

GLuint DrawableObject::getID() const {
    return objectID;
}

void DrawableObject::setSelected(bool sel) {
    selected = sel;
}

bool DrawableObject::isSelected() const {
    return selected;
}

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

void DrawableObject::addTexture(const std::shared_ptr<Texture>& texture, GLuint unit, const std::string& uniform)
{
    textures.push_back({texture, unit, uniform});
}

void DrawableObject::clearTextures()
{
    textures.clear();
}