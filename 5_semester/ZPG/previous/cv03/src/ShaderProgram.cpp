#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

ShaderProgram::ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath)
{
    // Load shader sources
    std::string vertexSource = loadShaderSource(vertexPath);
    std::string fragmentSource = loadShaderSource(fragmentPath);

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexSource, vertexShader, "VERTEX");

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentSource, fragmentShader, "FRAGMENT");

    // Link shaders into program
    programID = glCreateProgram();
    linkProgram(vertexShader, fragmentShader);

    // Clean up shaders as they are now linked into the program
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

    // Check for compilation errors
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

    // Check for linking errors
    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(programID, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        std::exit(EXIT_FAILURE);
    }
}