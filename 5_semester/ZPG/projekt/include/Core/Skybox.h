#pragma once

#include "Core/SkyboxModel.h"
#include "Core/Texture.h"
#include "Shaders/ShaderProgram.h"
#include <vector>
#include <string>
#include <memory>
#include <glm/glm.hpp>

class Skybox {
public:
    Skybox(const std::vector<std::string>& faces);
    ~Skybox();

    void render(const glm::mat4& view, const glm::mat4& projection);

private:
    std::shared_ptr<SkyboxModel> skyboxModel;
    std::shared_ptr<Texture> cubemapTexture;
    std::shared_ptr<ShaderProgram> skyboxShader;
};