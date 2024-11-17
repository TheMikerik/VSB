// Scene3.cpp
#include "../include/Scenes/Scene3.h"
#include "../models/sphere.h"

#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/TranslateOperation.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Scene3::Scene3(Camera& cam) : camera(cam) {

    this->addLight( Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)) );

    auto shader_const = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    auto shader_phong = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/fragment_phong.glsl");
    auto shader_lambert = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/fragment_lambert.glsl");
    auto shader_blinn = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/fragment_blinn.glsl");

    shaders = {shader_const, shader_phong, shader_lambert, shader_blinn};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
        for(auto& light : this->lights) {
            light.registerObserver(shader.get());
        }
    }

    for(auto& shader : shaders) {
        shader->use();
        glUniform1i(glGetUniformLocation(shader->getProgramID(), "numLights"), lights.size());
    }

    for(auto& light : this->lights) {
        light.notifyObservers();
    }
    
    camera.notifyObservers();

    std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));
    auto sphereModel = std::make_shared<Model>(sphereVertices);

    std::vector<glm::vec3> spherePositions = {
        glm::vec3( 2.0f,  2.0f,  0.0f),
        glm::vec3(-2.0f,  2.0f,  0.0f),
        glm::vec3( 2.0f, -2.0f,  0.0f),
        glm::vec3(-2.0f, -2.0f,  0.0f),
    };

    for(const auto& pos : spherePositions) {
        auto sphereDrawable = std::make_shared<DrawableObject>(sphereModel, shaders[currentShader]);

        Transformation sphereTrans;

        auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(3.0f));
        sphereTrans.addOperation(scaleOp);

        auto translateOp = std::make_shared<TranslateOperation>(pos);
        sphereTrans.addOperation(translateOp);

        sphereDrawable->setTransformation(sphereTrans);

        addDrawable(sphereDrawable);
    }
}

void Scene3::switchShader() {
    if (shaders.empty()) {
        std::cerr << "No shaders available to switch." << std::endl;
        return;
    }

    currentShader = (currentShader + 1) % shaders.size();
    std::cout << "Scene3: Switching to Shader Index: " << currentShader << std::endl;

    for(auto& drawable : drawables) {
        drawable->setShader(shaders[currentShader]);
    }

    shaders[currentShader]->use();
    camera.notifyObservers();
    for(auto& light : this->lights) {
        light.notifyObservers();
    }
}

void Scene3::addLight(const Light& light) {
    lights.push_back(light);
}

const std::vector<Light>& Scene3::getLights() const {
    return lights;
}