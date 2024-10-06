#include "Shader.h"
#include <glm/gtc/type_ptr.hpp> // Necessary for glm::value_ptr
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    // Read shader code from files
    std::string vertexCode = readShaderCode(vertexPath);
    std::string fragmentCode = readShaderCode(fragmentPath);

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // Compile Vertex Shader
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Compile Fragment Shader
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Link Shaders into Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // Delete Shaders as they're linked now
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    glDeleteProgram(ID);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    GLuint loc = glGetUniformLocation(ID, name.c_str());
    if(loc == -1){
        std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "| ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " 
                      << std::endl;
        }
    }
    else{
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "| ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " 
                      << std::endl;
        }
    }
}

std::string Shader::readShaderCode(const std::string& filePath) {
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    // Open the shader file
    shaderFile.open(filePath);
    if(!shaderFile.is_open()) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << filePath << std::endl;
        return "";
    }

    // Read the file's buffer contents into streams
    shaderStream << shaderFile.rdbuf();		

    // Close the file handler
    shaderFile.close();

    // Convert the stream into a string
    return shaderStream.str();
}