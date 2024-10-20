// ShaderProgram.h
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <GL/glew.h>
#include "ICameraObserver.h"
#include <glm/glm.hpp>

class ShaderProgram : public ICameraObserver {
public:
    ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
    ~ShaderProgram();

    void use() const;

    // Observer interface implementation
    void onCameraUpdate(const glm::mat4& view, const glm::mat4& projection) override;

    GLuint getProgramID() const { return programID; }

private:
    GLuint programID;

    std::string loadShaderSource(const std::string& filePath) const;
    void compileShader(const std::string& source, GLuint shader, const std::string& shaderType) const;
    void linkProgram(GLuint vertexShader, GLuint fragmentShader);

    // Uniform locations
    GLint viewLoc;
    GLint projLoc;
};

#endif // SHADERPROGRAM_H