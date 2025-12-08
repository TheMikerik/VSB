#pragma once

#include <string>
#include <GL/glew.h>
#include "Interfaces/ICameraObserver.h"
#include "Interfaces/ILightObserver.h"
#include <glm/glm.hpp>

class ShaderProgram : public ICameraObserver, public ILightObserver {
public:
    ShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
    ~ShaderProgram();

    void use() const;

    void onCameraUpdate(const glm::mat4& view, const glm::mat4& projection) override;
    void onLightUpdate(int inx, const glm::vec3& position, const glm::vec3& color) override;

    GLuint getProgramID() const { return programID; }

private:
    GLuint programID;

    std::string loadShaderSource(const std::string& filePath) const;
    void compileShader(const std::string& source, GLuint shader, const std::string& shaderType) const;
    void linkProgram(GLuint vertexShader, GLuint fragmentShader);

    GLint viewLoc;
    GLint projLoc;
    GLint lightPosLoc;
    GLint lightColorLoc;
    GLint viewPosLoc;
};