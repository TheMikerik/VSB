// Scene5.cpp
#include "Scenes/Scene5.h"
#include "Graphics/Light.h"

#include "../models/bushes.h"
#include "../models/tree.h"
#include "../models/platform.h"
#include "../models/gift.h"
#include "../models/sphere.h"
#include "../models/suzi_flat.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

Scene5::Scene5(Camera& cam, std::vector<Light>& ff) : camera(cam), fireflies(ff) {
    std::srand(static_cast<unsigned int>(std::time(0)));

    auto shader_platform = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader.glsl");
    auto shader_phong = std::make_shared<ShaderProgram>("./shaders/phong/vertex_phong.glsl", "./shaders/phong/fragment_phong.glsl");
    auto shader_white = std::make_shared<ShaderProgram>("./shaders/vertex_shader.glsl", "./shaders/fragment_shader_white.glsl");

    shaders = {shader_platform, shader_phong, shader_white};

    for(auto& shader : shaders) {
        camera.registerObserver(shader.get());
        for(auto& firefly : fireflies) {
            firefly.registerObserver(shader.get());
        }
    }

    for(auto& firefly : fireflies) {
        firefly.notifyObservers();
    }
    camera.notifyObservers();

    std::vector<float> platformVertices(std::begin(platform), std::end(platform));
    std::vector<float> treeVertices(std::begin(tree), std::end(tree));

    auto platformModel = std::make_shared<Model>(platformVertices);
    auto treeModel = std::make_shared<Model>(treeVertices);

    // Platform
    auto platformDrawable = std::make_shared<DrawableObject>(platformModel, shader_platform);
    addDrawable(platformDrawable);

    // // Spheres
    // for (int i = 0; i < 100; ++i) {
    //     auto randomShader = shaders[i % shaders.size()];
    //     auto sphereDrawable = std::make_shared<DrawableObject>(sphereModel, shader_phong);

    //     Transformation sphereTrans;
    //     sphereTrans.translate(glm::vec3(
    //         getRandom(-15.0f, 15.0f),
    //         getRandom(1.0f, 3.0f),
    //         getRandom(-15.0f, 15.0f)
    //     ));
    //     sphereTrans.rotate(getRandom(0.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //     sphereTrans.scale(glm::vec3(getRandom(0.2f, 0.8f)));
    //     sphereDrawable->setTransformation(sphereTrans);

    //     addDrawable(sphereDrawable);
    // }

    for (int i = 0; i < 100; ++i) {
        auto randomShader = shaders[i % shaders.size()];
        auto treeDrawable = std::make_shared<DrawableObject>(treeModel, shader_phong);

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

    // Fireflies
    for(auto& firefly : fireflies) {
        std::vector<float> sphereVertices(std::begin(sphere), std::end(sphere));
        auto sphereModel = std::make_shared<Model>(sphereVertices);
        auto lightShader = shader_white;

        auto lightDrawable = std::make_shared<DrawableObject>(sphereModel, lightShader);

        Transformation lightTrans;
        lightTrans.translate(firefly.getPosition());
        lightTrans.scale(glm::vec3(0.2f));

        lightDrawable->setTransformation(lightTrans);
        addDrawable(lightDrawable);
    }
}

float Scene5::getRandom(float min, float max) {
    return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}