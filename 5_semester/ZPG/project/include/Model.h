#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

class Model {
public:
    Model(const std::vector<float>& vertices, 
        const std::string& fragmentPath, 
        const std::string& vertexPath = "./shaders/vertex_shader.glsl");

    ~Model();

    void render() const;
    void setModelMatrix(const glm::mat4& matrix);
    glm::mat4 getModelMatrix() const;

private:
    GLuint VAO;
    GLuint VBO;
    GLuint shaderProgram;
    GLsizei vertexCount;
    glm::mat4 modelMatrix;

    std::string loadShaderSource(const std::string& filePath) const;
    GLuint createShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) const;
    void compileShader(const std::string& source, GLuint shader, const std::string& shaderType) const;
    void linkProgram(GLuint program, GLuint vertexShader, GLuint fragmentShader) const;
};