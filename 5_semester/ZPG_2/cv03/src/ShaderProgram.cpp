#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
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