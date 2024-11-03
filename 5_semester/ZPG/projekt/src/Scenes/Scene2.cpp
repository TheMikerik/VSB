// Scene2.cpp
#include "../include/Scenes/Scene2.h"
#include "../models/bushes.h"
#include "../models/tree.h"
#include "../models/platform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

Scene2::Scene2(Camera& cam) : camera(cam) {
    std::srand(static_cast<unsigned int>(std::time(0)));
    setBackgroundColor(glm::vec4(0.59f, 0.76f, 0.92f, 1.0f));

    auto shader_uni = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    auto shader_red = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_red.glsl");
    auto shader_purple = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_purple.glsl");
    auto shader_green = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_green.glsl");

    shaders = {shader_uni, shader_red, shader_purple, shader_green};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
    }

    camera.notifyObservers();

    std::vector<float> bushesVertices(std::begin(bushes), std::end(bushes));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));
    std::vector<float> platformVertices(std::begin(platform), std::end(platform));

    auto bushesModel = std::make_shared<Model>(bushesVertices);
    auto treeModel = std::make_shared<Model>(treeVertices);
    auto platformModel = std::make_shared<Model>(platformVertices);

    // Platform
    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_uni);
    addDrawable(platformDrawable);

    // Bushes
    for (int i = 0; i < 300; ++i) {
        auto randomShader = shaders[i % shaders.size()];
        auto bushesDrawable = std::make_shared<DrawableObject>(bushesModel, randomShader);

        Transformation bushesTrans;
        bushesTrans.translate(glm::vec3(
            getRandom(-15.0f, 15.0f),
            0.0f,
            getRandom(-15.0f, 15.0f)
        ));
        bushesTrans.rotate(getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        bushesTrans.scale(glm::vec3(getRandom(1.0f, 3.0f)));
        bushesDrawable->setTransformation(bushesTrans);

        addDrawable(bushesDrawable);
    }

    // Trees
    for (int i = 0; i < 100; ++i) {
        auto randomShader = shaders[i % shaders.size()];
        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, randomShader);

        Transformation treeTrans;
        treeTrans.translate(glm::vec3(
            getRandom(-15.0f, 15.0f),
            0.0f,
            getRandom(-15.0f, 15.0f)
        ));
        treeTrans.rotate(getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        treeTrans.scale(glm::vec3(getRandom(0.2f, 0.8f)));
        treeDrawable->setTransformation(treeTrans);

        addDrawable(treeDrawable);
    }
}

float Scene2::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}