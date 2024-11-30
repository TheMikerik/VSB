// Scene6.cpp
#include "Scenes/Scene6.h"
#include "Graphics/Light.h"
#include "Graphics/Spotlight.h"    // Include the Spotlight header
#include "../models/tree.h"
#include "../models/platform.h"
#include "../models/sphere.h"
#include "../include/Core/Transformation/ScaleOperation.h"
#include "../include/Core/Transformation/TranslateOperation.h"
#include "../include/Core/Transformation/RotateOperation.h"
#include "../include/Core/Material.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <iostream>

Scene6::Scene6(Camera& cam) : camera(cam), spotlight(std::make_shared<Spotlight>(glm::vec3(5.0f, 4.0f, 5.0f), glm::vec3(1.0f, 0.0f, 1.0f))) {
    auto shader_platform = std::make_shared<ShaderProgram>("./shaders/v_l.glsl", "./shaders/f.glsl");
    auto shader_sl = std::make_shared<ShaderProgram>("./shaders/v_l.glsl", "./shaders/f_l.glsl");

    shaders = {shader_platform, shader_sl};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
    }
    
    camera.notifyObservers();

    std::vector<float> platformVertices(std::begin(platform), std::end(platform));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));

    auto platformModel = std::make_shared<Model>(platformVertices);
    auto treeModel = std::make_shared<Model>(treeVertices);

    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_platform);

    Material platformMaterial(
        glm::vec3(0.3f, 0.3f, 0.3f), // Ambient
        glm::vec3(0.6f, 0.6f, 0.6f), // Diffuse
        glm::vec3(0.8f, 0.8f, 0.8f), // Specular
        64.0f                        // Shininess
    );
    platformDrawable->setMaterial(platformMaterial);

    Transformation platformTrans;
    auto scaleOp = std::make_shared<ScaleOperation>(glm::vec3(5.0f, 1.0f, 5.0f));
    platformTrans.addOperation(scaleOp);
    platformDrawable->setTransformation(platformTrans);


    addDrawable(platformDrawable);

    for (int i = 0; i < 300; ++i) {
        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, shader_sl);

        Transformation treeTrans;

        auto translateOp = std::make_shared<TranslateOperation>(
            glm::vec3(getRandom(-75.0f, 75.0f), 0.0f, getRandom(-75.0f, 75.0f)));
        treeTrans.addOperation(translateOp);

        auto scaleOp = std::make_shared<ScaleOperation>(
            glm::vec3(getRandom(0.2f, 1.2f)));
        treeTrans.addOperation(scaleOp);

        auto rotateOp = std::make_shared<RotateOperation>(
            getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        treeTrans.addOperation(rotateOp);

        treeDrawable->setTransformation(treeTrans);

        Material treeMaterial(
            glm::vec3(0.2f, 0.2f, 0.2f), // Ambient
            glm::vec3(0.5f, 0.5f, 0.5f), // Diffuse
            glm::vec3(0.7f, 0.7f, 0.7f), // Specular
            32.0f                        // Shininess
        );
        treeDrawable->setMaterial(treeMaterial);

        if (i % 6 == 0){
            treeDrawables.push_back(treeDrawable);
        }

        addDrawable(treeDrawable);
    }
}

void Scene6::render(float dt) {
    for (auto& treeDrawable : treeDrawables) {
        auto trans = treeDrawable->getTransformation();
        auto rotateOp = std::make_shared<RotateOperation>(dt * 50, glm::vec3(0.0f, 1.0f, 0.0f));
        trans.addOperation(rotateOp);
        treeDrawable->setTransformation(trans);

        treeDrawable->render();
    }

    glm::vec3 spotlightPos = camera.getPosition();
    glm::vec3 spotlightDir = glm::normalize(camera.getFront());
    spotlight->update(spotlightPos, spotlightDir);

    for (auto& shader : shaders) {
        spotlight->applyToShader(shader);
    }

    Scene::render(dt);
}

float Scene6::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}