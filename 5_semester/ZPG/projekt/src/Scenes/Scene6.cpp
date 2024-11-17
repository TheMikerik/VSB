// Scene6.cpp
#include "Scenes/Scene6.h"
#include "Graphics/Light.h"

#include "../models/tree.h"
#include "../models/platform.h"
#include "../models/sphere.h"

#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/TranslateOperation.h"
#include "../include/Core/Transformation/RotateOperation.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <iostream>

Scene6::Scene6(Camera& cam) : camera(cam) {
    glm::vec3 positions[4] = {
        glm::vec3(-11.0f, 5.0f, -11.0f),
        glm::vec3(11.0f, 5.0f, -11.0f),
        glm::vec3(-11.0f, 5.0f, 11.0f),
        glm::vec3(11.0f, 5.0f, 11.0f)
    };
    
    glm::vec3 color = glm::vec3(4.0f);
    
    for (int i = 0; i < 4; ++i) {
        this->addLight(Light(positions[i], color));
    }

    auto shader_platform = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    auto shader_const = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_constant.glsl");

    auto shader_phong = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/depth_fragment_phong.glsl");
    auto shader_lambert = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/depth_fragment_lambert.glsl");
    auto shader_blinn = std::make_shared<ShaderProgram>("./shaders/light_shaders/vertex_shader_with_lights.glsl", "./shaders/light_shaders/depth_fragment_blinn.glsl");

    shaders = {shader_platform, shader_const, shader_phong, shader_lambert, shader_blinn};

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

    for (size_t i = 0; i < this->lights.size(); ++i) {
        for(auto& shader : shaders) {
            shader->onLightUpdate(i, lights[i].getPosition(), lights[i].getColor());
        }
        lights[i].notifyObservers(i);
    }
    
    camera.notifyObservers();

    std::vector<float> platformVertices(std::begin(platform), std::end(platform));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));

    auto platformModel = std::make_shared<Model>(platformVertices);
    auto treeModel = std::make_shared<Model>(treeVertices);

    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_phong);
    addDrawable(platformDrawable);

    for (int i = 0; i < 100; ++i) {
        int shaderIndex = rand() % 3;
        std::shared_ptr<ShaderProgram> selectedShader;
        switch(shaderIndex) {
            case 0: selectedShader = shader_phong; break;
            case 1: selectedShader = shader_lambert; break;
            case 2: selectedShader = shader_blinn; break;
        }

        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, selectedShader);

        Transformation treeTrans;

        auto translateOp = std::make_shared<TranslateOperation>(
            glm::vec3(getRandom(-15.0f, 15.0f), 0.0f, getRandom(-15.0f, 15.0f)));
        treeTrans.addOperation(translateOp);

        auto scaleOp = std::make_shared<ScaleOperation>(
            glm::vec3(getRandom(0.2f, 0.8f)));
        treeTrans.addOperation(scaleOp);

        // Initial rotation, just to set a base value
        auto rotateOp = std::make_shared<RotateOperation>(
            getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        treeTrans.addOperation(rotateOp);

        treeDrawable->setTransformation(treeTrans);

        if (i % 6 == 0){
            treeDrawables.push_back(treeDrawable);
        }

        addDrawable(treeDrawable);
    }

    for(auto& light : this->getLights()) {
        std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));
        auto sphereModel = std::make_shared<Model>(sphereVertices);
        auto lightShader = shader_const;

        auto lightDrawable = std::make_shared<DrawableObject>(sphereModel, lightShader);
        Transformation lightTrans;

        auto translateOp = std::make_shared<TranslateOperation>(light.getPosition());
        lightTrans.addOperation(translateOp);
        auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(0.2f));
        lightTrans.addOperation(scaleOp);

        lightDrawable->setTransformation(lightTrans);
        addDrawable(lightDrawable);
    }
}

float Scene6::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void Scene6::addLight(const Light& light) {
    lights.push_back(light);
}

const std::vector<Light>& Scene6::getLights() const {
    return lights;
}

void Scene6::render(float dt) {

    for (auto& treeDrawable : treeDrawables) {
        auto trans = treeDrawable->getTransformation();
        auto rotateOp = std::make_shared<RotateOperation>(dt * 50, glm::vec3(0.0f, 1.0f, 0.0f));
        trans.addOperation(rotateOp);
        treeDrawable->setTransformation(trans);
    }

    Scene::render(dt);
}