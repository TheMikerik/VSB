#include "Shaders/ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
    : viewLoc(-1), projLoc(-1), lightPosLoc(-1), lightColorLoc(-1), viewPosLoc(-1)
{
    std::string vertexSource = loadShaderSource(vertexPath);
    std::string fragmentSource = loadShaderSource(fragmentPath);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexSource, vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentSource, fragmentShader, "FRAGMENT");

    programID = glCreateProgram();
    linkProgram(vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Get uniform locations
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

std::string ShaderProgram::loadShaderSource(const std::string& filePath) const
{
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

void ShaderProgram::compileShader(const std::string& source, GLuint shader, const std::string& shaderType) const
{
    const char* shaderCode = source.c_str();
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void ShaderProgram::linkProgram(GLuint vertexShader, GLuint fragmentShader)
{
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(programID, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        std::exit(EXIT_FAILURE);
    }
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
}

void ShaderProgram::onLightUpdate(const glm::vec3& position, const glm::vec3& color)
{
    use();
    if (lightPosLoc != -1) {
        glUniform3fv(lightPosLoc, 1, glm::value_ptr(position));
    }
    if (lightColorLoc != -1) {
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(color));
    }
}