#pragma once

<<<<<<< HEAD
#include "Core/SkyboxModel.h"      
=======
#include "Core/SkyboxModel.h"
>>>>>>> 783003c0f8698c5a6a0d2f713c85ebf89823a7c5
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
<<<<<<< HEAD
    std::shared_ptr<SkyboxModel> skyboxModel;  
=======
    std::shared_ptr<SkyboxModel> skyboxModel;
>>>>>>> 783003c0f8698c5a6a0d2f713c85ebf89823a7c5
    std::shared_ptr<Texture> cubemapTexture;
    std::shared_ptr<ShaderProgram> skyboxShader;
};