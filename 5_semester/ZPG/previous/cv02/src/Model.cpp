// Model.cpp
#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

Model::Model(const std::vector<float>& vertices, 
            const std::string& fragmentPath, 
            const std::string& vertexPath)
    : VAO(0), VBO(0), shaderProgram(0), vertexCount(0) 
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    vertexCount = static_cast<GLsizei>(vertices.size() / 3);

    shaderProgram = createShaderProgram(vertexPath, fragmentPath);
}

Model::~Model() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}

void Model::render() const {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

std::string Model::loadShaderSource(const std::string& filePath) const {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

void Model::compileShader(const std::string& source, GLuint shader, const std::string& shaderType) const {
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

void Model::linkProgram(GLuint program, GLuint vertexShader, GLuint fragmentShader) const {
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

GLuint Model::createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) const {
    std::string vertexSource = loadShaderSource(vertexPath);
    std::string fragmentSource = loadShaderSource(fragmentPath);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexSource, vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentSource, fragmentShader, "FRAGMENT");

    GLuint program = glCreateProgram();
    linkProgram(program, vertexShader, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}