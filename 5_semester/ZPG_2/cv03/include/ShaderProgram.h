#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <GL/glew.h>

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
    ~ShaderProgram();

    void use() const;
    GLuint getProgramID() const { return programID; }

private:
    GLuint programID;

    std::string loadShaderSource(const std::string& filePath) const;
    void compileShader(const std::string& source, GLuint shader, const std::string& shaderType) const;
    void linkProgram(GLuint vertexShader, GLuint fragmentShader);
};

#endif // SHADERPROGRAM_H