#include "Shaders/ShaderProgram.h"
#include "Shaders/ShaderLoader.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
    : viewLoc(-1), projLoc(-1), lightPosLoc(-1), lightColorLoc(-1), viewPosLoc(-1)
{
    ShaderLoader shaderLoader;
    this->programID = shaderLoader.loadShader(vertexPath.c_str(), fragmentPath.c_str());

    viewLoc = glGetUniformLocation(programID, "viewMatrix");
    projLoc = glGetUniformLocation(programID, "projectionMatrix");
    lightPosLoc = glGetUniformLocation(programID, "lightPos");
    lightColorLoc = glGetUniformLocation(programID, "lightColor");
    viewPosLoc = glGetUniformLocation(programID, "viewPos");
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(programID);
}

void ShaderProgram::use() const
{
    glUseProgram(programID);
}

void ShaderProgram::onCameraUpdate(const glm::mat4& view, const glm::mat4& projection)
{
    use();
    if (viewLoc != -1) {
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    }
    if (projLoc != -1) {
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    }

    glm::mat4 inverseView = glm::inverse(view);
    glm::vec3 cameraPos = glm::vec3(inverseView[3]);
    
    if (viewPosLoc != -1) {
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(cameraPos));
    }
    glUseProgram(0);
}

void ShaderProgram::onLightUpdate(int lightIndex, const glm::vec3& position, const glm::vec3& color) {
    use();
    std::string posArray = "lightPos[" + std::to_string(lightIndex) + "]";
    std::string colorArray = "lightColor[" + std::to_string(lightIndex) + "]";
    GLint posLoc = glGetUniformLocation(programID, posArray.c_str());
    GLint colorLoc = glGetUniformLocation(programID, colorArray.c_str());
    if (posLoc != -1) glUniform3fv(posLoc, 1, glm::value_ptr(position));
    if (colorLoc != -1) glUniform3fv(colorLoc, 1, glm::value_ptr(color));
    glUseProgram(0);
}

void ShaderProgram::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void ShaderProgram::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    GLint loc = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}