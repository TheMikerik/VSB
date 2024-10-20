#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Model {
public:
    Model(const std::vector<float>& vertices, 
          const std::string& fragmentPath, 
          const std::string& vertexPath = "./shaders/vertex_shader.glsl");

    ~Model();

    void render() const;

private:
    GLuint VAO;
    GLuint VBO;
    GLuint shaderProgram;
    GLsizei vertexCount;

    std::string loadShaderSource(const std::string& filePath) const;
    GLuint createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) const;
    void compileShader(const std::string& source, GLuint shader, const std::string& shaderType) const;
    void linkProgram(GLuint program, GLuint vertexShader, GLuint fragmentShader) const;
};