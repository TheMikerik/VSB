#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    GLuint ID;

    // Constructor that builds the shader program from vertex and fragment shader file paths
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    // Activate the shader
    void use();

    // Utility uniform functions
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    void checkCompileErrors(GLuint shader, std::string type);
    std::string readShaderCode(const std::string& filePath);
};

#endif // SHADER_H