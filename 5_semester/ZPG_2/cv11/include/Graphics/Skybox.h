#pragma once

#include <memory>
#include <vector>
#include <string>
#include <GL/glew.h>
#include "Core/Model.h"
#include "Core/Texture.h"
#include "Shaders/ShaderProgram.h"
#include "Graphics/Camera.h"
#include "Interfaces/ICameraObserver.h"

class Skybox : public ICameraObserver {
public:
    Skybox(const std::vector<std::string>& faces);
    ~Skybox() = default;

    void render() const;
    void onCameraUpdate(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
    std::shared_ptr<Model> model;
    std::shared_ptr<Texture> cubemapTexture;
    std::shared_ptr<ShaderProgram> shader;
    
    glm::mat4 view;
    glm::mat4 projection;
};