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
    auto shader_platform = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    auto shader_const = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_constant.glsl");


    shaders = {shader_platform, shader_const};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
    }
    
    camera.notifyObservers();

    std::vector<float> platformVertices(std::begin(platform), std::end(platform));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));

    auto platformModel = std::make_shared<Model>(platformVertices);
    auto treeModel = std::make_shared<Model>(treeVertices);

    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_platform);
    addDrawable(platformDrawable);

    for (int i = 0; i < 100; ++i) {
        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, shader_platform);

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
}

float Scene6::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
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