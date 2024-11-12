// Scene5.cpp
#include "Scenes/Scene5.h"
#include "Graphics/Light.h"

#include "../models/bushes.h"
#include "../models/tree.h"
#include "../models/platform.h"
#include "../models/gift.h"
#include "../models/sphere.h"
#include "../models/suzi_flat.h"

#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/TranslateOperation.h"
#include "../include/Core/Transformation/RotateOperation.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

Scene5::Scene5(Camera& cam) : camera(cam) { // Update this line
    std::srand(static_cast<unsigned int>(std::time(0)));

    for (int i = 0; i < 10; ++i) {
        glm::vec3 position = glm::vec3(
            static_cast<float>(rand() % 30 - 15),
            static_cast<float>(rand() % 10 + 1),
            static_cast<float>(rand() % 30 - 15)
        );
        glm::vec3 color = glm::vec3(1.0f);
        this->addLight(Light(position, color));
    }

    auto shader_platform = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    auto shader_phong = std::make_shared<ShaderProgram>("./shaders/phong/vertex_phong.glsl", "./shaders/phong/fragment_phong.glsl");
    auto shader_white = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_white.glsl");

    shaders = {shader_platform, shader_phong, shader_white};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
        for(auto& light : this->lights) {
            light.registerObserver(shader.get());
        }
    }

    for(auto& light : this->lights) {
        light.notifyObservers();
    }
    camera.notifyObservers();

    std::vector<float> platformVertices(std::begin(platform), std::end(platform));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));

    auto platformModel = std::make_shared<Model>(platformVertices);
    auto treeModel = std::make_shared<Model>(treeVertices);

    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_platform);
    addDrawable(platformDrawable);

    for (int i = 0; i < 100; ++i) {
        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, shader_phong);

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

        if (i % 9 == 0){
            treeDrawables.push_back(treeDrawable);
        }
        addDrawable(treeDrawable);
    }


    for(auto& firefly : this->getLights()) {
        std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));
        auto sphereModel = std::make_shared<Model>(sphereVertices);
        auto lightShader = shader_white;

        auto lightDrawable = std::make_shared<DrawableObject>(sphereModel, lightShader);
        Transformation lightTrans;

        auto translateOp = std::make_shared<TranslateOperation>(firefly.getPosition());
        lightTrans.addOperation(translateOp);
        auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(0.2f));
        lightTrans.addOperation(scaleOp);

        lightDrawable->setTransformation(lightTrans);

        glm::vec3 initialDirection(getRandom(-1.0f, 1.0f), getRandom(-1.0f, 1.0f), getRandom(-1.0f, 1.0f));
        lightDrawablesWithDirection.emplace_back(lightDrawable, glm::normalize(initialDirection));

        addDrawable(lightDrawable);
    }
}

float Scene5::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

void Scene5::addLight(const Light& light) {
    lights.push_back(light);
}

const std::vector<Light>& Scene5::getLights() const {
    return lights;
}

void Scene5::render(float dt) {

    for (auto& treeDrawable : treeDrawables) {
        auto trans = treeDrawable->getTransformation();
        auto rotateOp = std::make_shared<RotateOperation>(dt * 50, glm::vec3(0.0f, 1.0f, 0.0f));
        trans.addOperation(rotateOp);
        treeDrawable->setTransformation(trans);
    }

    for (size_t i = 0; i < lightDrawablesWithDirection.size(); ++i) {
        auto& item = lightDrawablesWithDirection[i];
        auto& lightDrawable = item.drawable;
        auto& direction = item.direction;

        auto trans = lightDrawable->getTransformation();
        glm::mat4 modelMatrix = trans.getModelMatrix();
        glm::vec3 currentPosition = glm::vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
        glm::vec3 newPosition = currentPosition + direction * dt * 4.0f;

        if (newPosition.x >= 15.0f || newPosition.x <= -15.0f) direction.x *= -1.0f;
        if (newPosition.y >= 10.0f || newPosition.y <= 1.0f) direction.y *= -1.0f;
        if (newPosition.z >= 15.0f || newPosition.z <= -15.0f) direction.z *= -1.0f;

        trans.clearOperations();
        auto translateOp = std::make_shared<TranslateOperation>(newPosition);
        trans.addOperation(translateOp);

        auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(0.2f));
        trans.addOperation(scaleOp);
        
        lightDrawable->setTransformation(trans);

        if (i < this->lights.size()) {
            this->lights[i].setPosition(newPosition);
        }
    }
    Scene::render(dt);
}
